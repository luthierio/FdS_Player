#ifndef FileManager_H
#define FileManager_H

#include <SdFat.h>

class FileManager {
public:
  FileManager(SdFat* sdInstance)
      : sd(sdInstance), errorCallback(nullptr),
        onBeforeLoad(nullptr), onAfterLoad(nullptr),
        onBeforeSave(nullptr), onAfterSave(nullptr) {}

  // Définition du type de fonction de rappel
  typedef void (*CallbackFunction)(const char* fileName, const char* message);

  // Ajout de cinq fonctions de rappel
  CallbackFunction errorCallback;
  CallbackFunction onBeforeLoad;
  CallbackFunction onAfterLoad;
  CallbackFunction onBeforeSave;
  CallbackFunction onAfterSave;

  // Méthode pour définir les fonctions de rappel
  void setCallbacks(CallbackFunction error, CallbackFunction beforeLoad, 
                    CallbackFunction afterLoad, CallbackFunction beforeSave, 
                    CallbackFunction afterSave) {
    errorCallback = error;
    onBeforeLoad = beforeLoad;
    onAfterLoad = afterLoad;
    onBeforeSave = beforeSave;
    onAfterSave = afterSave;
  }

  bool save(const char* nomFichier, const void* dataPointer, size_t dataSize, bool silent = false) {
    sd->open("/");
    if (fileExists(nomFichier) && !createBackup(nomFichier)) {
      if (errorCallback) errorCallback(nomFichier, "Le fichier existe, mais la création du backup a échoué");
      return false;
    }

    File fichier = sd->open(nomFichier, O_WRITE | O_CREAT | O_TRUNC);
    if (fichier) {
      if (onBeforeSave && !silent) onBeforeSave(nomFichier, nullptr);  // Appel de la fonction de rappel avant la sauvegarde
      if (fichier.write(dataPointer, dataSize) == dataSize) {
        fichier.close();
        if (onAfterSave && !silent) onAfterSave(nomFichier, "OK!");  // Appel de la fonction de rappel après la sauvegarde
        return true;
      } else {
        fichier.close();
        restoreBackup(nomFichier);
        if (errorCallback) errorCallback(nomFichier, "Ecriture impossible");
      }
    }
    fichier.close();

    return false;
  }

  bool load(const char* nomFichier, void* dataPointer, size_t dataSize, bool silent = false) {
    if (fileExists(nomFichier)) {
      File fichier = sd->open(nomFichier, O_RDONLY);
      if (fichier) {
        if (onBeforeLoad && !silent) onBeforeLoad(nomFichier, nullptr);  // Appel de la fonction de rappel avant le chargement
        if (fichier.read(dataPointer, dataSize) == dataSize) {
          fichier.close();
          if (onAfterLoad && !silent) onAfterLoad(nomFichier, "OK");  // Appel de la fonction de rappel après le chargement
          return true;
        } else {
          if (errorCallback) errorCallback(nomFichier, "Erreur de lecture");
        }
      }
    } else {
      if (onAfterLoad && !silent) onAfterLoad(nomFichier, "Rien à charger");  // Appel de la fonction de rappel après le chargement
    }

    return false;
  }

private:
  static const size_t MAX_FILE_NAME_LENGTH = 255;
  SdFat* sd;

  bool fileExists(const char* nomFichier) {
    sd->chdir();
    return sd->exists(nomFichier);
  }

  bool createBackup(const char* nomFichier) {
    const char* suffixeBackup = ".bkp";
    char nomFichierBackup[MAX_FILE_NAME_LENGTH];

    if (strlen(nomFichier) + strlen(suffixeBackup) > MAX_FILE_NAME_LENGTH - 1) {
      if (errorCallback) errorCallback(nomFichier, "Le nom de fichier avec le suffixe de backup dépasse la limite de taille");
      return false;
    }

    strcpy(nomFichierBackup, nomFichier);
    strcat(nomFichierBackup, suffixeBackup);

    sd->rename(nomFichier, nomFichierBackup);

    if (sd->exists(nomFichierBackup)) {
      return true;
    } else {
      if (errorCallback) errorCallback(nomFichier, "Erreur lors de la création du backup");
    }

    return false;
  }

  void restoreBackup(const char* nomFichier) {
    const char* suffixeBackup = ".bkp";
    char nomFichierBackup[MAX_FILE_NAME_LENGTH];

    if (strlen(nomFichier) + strlen(suffixeBackup) > MAX_FILE_NAME_LENGTH - 1) {
      if (errorCallback) errorCallback(nomFichier, "Le nom de fichier avec le suffixe de backup dépasse la limite de taille");
      return;
    }

    strcpy(nomFichierBackup, nomFichier);
    strcat(nomFichierBackup, suffixeBackup);

    if (sd->exists(nomFichierBackup)) sd->rename(nomFichierBackup, nomFichier);
  }
};

#endif

