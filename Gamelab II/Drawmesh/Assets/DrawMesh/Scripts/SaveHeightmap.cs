using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class SaveHeightmap : MonoBehaviour
{
    string Startingpath;
    string Endpath;
    string fileName = "saved";
    public MessageHandler messageHandler;

   public void OnClick() {
          Startingpath = "Assets/TempHeightmaps/000.png";
          Endpath = "Assets/SavedHeightmaps/" + fileName + ".png";

          var rawData = System.IO.File.ReadAllBytes(Startingpath);
          System.IO.File.WriteAllBytes(Endpath, rawData);
          StartCoroutine(messageHandler.showMessage("Heightmap saved in Assets/SavedHeightmaps/" + fileName + ".png"));
          AssetDatabase.Refresh();
   }


   public void setName(string name) {
        fileName = name;
   }
}
