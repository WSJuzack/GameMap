using UnityEditor;
using UnityEngine;
using System.IO;
using UnityEditor.Scripting.Python;

public class CallPythonCode : MonoBehaviour
{


    public void callPython()
    {
        PythonRunner.EnsureInitialized();
        PythonRunner.RunFile(Path.Combine(Application.dataPath, @"PythonScripts/Main.py"));
    }
}


