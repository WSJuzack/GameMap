using UnityEditor;
using UnityEditor.Scripting.Python;

public class MenuItem_Main_Class
{
   [MenuItem("Python Scripts/Main")]
   public static void Main()
   {
       PythonRunner.RunFile("Assets/PythonScripts/Main.py");
       }
};
