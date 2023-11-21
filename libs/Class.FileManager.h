#ifndef FileManager_H
#define FileManager_H

#include <SdFat.h>

class FileManager {
public:
  FileManager(SdFat* sdInstance)
      : sd(sdInstance), lastMessage(nullptr), onBeforeLoad(nullptr), onAfterLoad(nullptr),
        onBeforeSave(nullptr), onAfterSave(nullptr) {}

  // Définition du type de fonction de rappel
  typedef void (*CallbackFunction)();

  // Ajout de quatre fonctions de rappel
  CallbackFunction onBeforeLoad;
  CallbackFunction onAfterLoad;
  CallbackFunction onBeforeSave;
  CallbackFunction onAfterSave;

  // Méthode pour définir les fonctions de rappel
  void setCallbacks(CallbackFunction beforeLoad, CallbackFunction afterLoad,
                    CallbackFunction beforeSave, CallbackFunction afterSave) {
    onBeforeLoad = beforeLoad;
    onAfterLoad = afterLoad;
    onBeforeSave = beforeSave;
    onAfterSave = afterSave;
  }

  bool save(const char* nomFichier, const void* dataPointer, size_t dataSize) {
    sd->open("/");
    if (fileExists(nomFichier) && !createBackup(nomFichier)) {
      setLastMessage(F("Le fichier existe, mais la création du backup a échoué"));
      return false;
    }

    File fichier = sd->open(nomFichier, O_WRITE | O_CREAT | O_TRUNC);
    if (fichier) {
      if (onBeforeSave) onBeforeSave();  // Appel de la fonction de rappel avant la sauvegarde
      if (fichier.write(dataPointer, dataSize) == dataSize) {
        fichier.close();
        setLastMessage(F("Sauvegarde OK!"));
        if (onAfterSave) onAfterSave();  // Appel de la fonction de rappel après la sauvegarde
        return true;
      } else {
        fichier.close();
        setLastMessage(F("Ecriture impossible"));
        restoreBackup(nomFichier);
      }
    }
    fichier.close();

    return false;
  }

  bool load(const char* nomFichier, void* dataPointer, size_t dataSize) {
    if (fileExists(nomFichier)) {
      File fichier = sd->open(nomFichier, O_RDONLY);
      if (fichier) {
        if (onBeforeLoad) onBeforeLoad();  // Appel de la fonction de rappel avant le chargement
        if (fichier.read(dataPointer, dataSize) == dataSize) {
          fichier.close();
          setLastMessage(F("Chargement OK!"));
          if (onAfterLoad) onAfterLoad();  // Appel de la fonction de rappel après le chargement
          return true;
        } else {
          setLastMessage(F("Erreur de lecture"));
        }
      }
    } else {
      setLastMessage(F("Fichier inexistant"));
    }

    return false;
  }

  const __FlashStringHelper* getLastMessage() const {
    return lastMessage;
  }

private:
  static const size_t MAX_FILE_NAME_LENGTH = 255;
  SdFat* sd;
  const __FlashStringHelper* lastMessage;

  bool fileExists(const char* nomFichier) {
    sd->chdir();
    return sd->exists(nomFichier);
  }

  bool createBackup(const char* nomFichier) {
    const char* suffixeBackup = ".bkp";
    char nomFichierBackup[MAX_FILE_NAME_LENGTH];

    if (strlen(nomFichier) + strlen(suffixeBackup) > MAX_FILE_NAME_LENGTH - 1) {
      setLastMessage(F("Le nom de fichier avec le suffixe de backup dépasse la limite de taille"));
      return false;
    }

    strcpy(nomFichierBackup, nomFichier);
    strcat(nomFichierBackup, suffixeBackup);

    sd->rename(nomFichier, nomFichierBackup);

    if (sd->exists(nomFichierBackup)) {
      setLastMessage(F("Création du backup OK"));
      return true;
    } else {
      setLastMessage(F("Erreur lors de la création du backup"));
    }

    return false;
  }

  void restoreBackup(const char* nomFichier) {
    const char* suffixeBackup = ".bkp";
    char nomFichierBackup[MAX_FILE_NAME_LENGTH];

    if (strlen(nomFichier) + strlen(suffixeBackup) > MAX_FILE_NAME_LENGTH - 1) {
      setLastMessage(F("Le nom de fichier avec le suffixe de backup dépasse la limite de taille"));
      return;
    }

    strcpy(nomFichierBackup, nomFichier);
    strcat(nomFichierBackup, suffixeBackup);

    if (sd->exists(nomFichierBackup)) sd->rename(nomFichierBackup, nomFichier);
  }

  bool loadDataSize(const char* nomFichier, size_t& dataSize) {
    File fichier = sd->open(nomFichier, O_RDONLY);
    if (fichier) {
      dataSize = fichier.fileSize();
      fichier.close();
      return true;
    } else {
      return false;
    }
  }

  void setLastMessage(const __FlashStringHelper* message) {
    lastMessage = message;
    //Serial.println(message);
  }
};

#endif
