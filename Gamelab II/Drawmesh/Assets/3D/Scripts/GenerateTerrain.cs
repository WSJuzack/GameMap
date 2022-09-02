using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class GenerateTerrain : MonoBehaviour
{
    public Terrain terrain;
    public Texture2D tex;
    public int size;
    // Start is called before the first frame update
    void Start()
    {
        string path = "Assets/TempHeightmaps/000.png";
        TextureImporter A = (TextureImporter)AssetImporter.GetAtPath(path);
        A.isReadable = true;
        AssetDatabase.ImportAsset(path, ImportAssetOptions.ForceUpdate);
        tex = AssetDatabase.LoadAssetAtPath<Texture2D>(path);
        updateTerrainHeightmap();
    }

    private void updateTerrainHeightmap()
    {
        terrain.terrainData.heightmapResolution = size;
        float[,] f = new float[1, 1];
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                f[0, 0] = tex.GetPixel(x, y).grayscale;
                terrain.terrainData.SetHeights(x, y, f);
            }
        }
        //terrain.Flush();
        terrain.terrainData.SyncHeightmap();

    }
}
