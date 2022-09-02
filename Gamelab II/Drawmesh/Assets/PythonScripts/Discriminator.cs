using UnityEditor;
using UnityEditor.Scripting.Python;

public class MenuItem_Discriminator_Class
{
   [MenuItem("Python Scripts/Discriminator")]
   public static void Discriminator()
   {
       PythonRunner.RunFile("Assets/PythonScripts/Discriminator.py");
       }
};
