using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class NameChanger : MonoBehaviour
{
    public TextMeshProUGUI fileName;
    public SaveHeightmap Script;
    
   public void Change() {
        Script.setName(fileName.text);
   }
}
