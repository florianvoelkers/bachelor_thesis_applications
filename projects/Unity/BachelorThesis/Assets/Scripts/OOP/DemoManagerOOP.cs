using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DemoManagerOOP : MonoBehaviour
{
    [SerializeField] public static float leftBound = -103.0f;
    [SerializeField] public static float rightBound = 103.0f;
    [SerializeField] public static float topBound = 58.0f;
    [SerializeField] public static float bottomBound = -58.0f;

    [SerializeField] private GameObject parentObject;
    [SerializeField] private int initialObjectCount;
    [SerializeField] private int addObjectCount;
    [SerializeField] private GameObject objectToSpawn;
    [SerializeField] private Text objectCountText;

    private int objectCount = 0;

    private void Start()
    {
        SpawnObjects(initialObjectCount);
        objectCountText.text = objectCount.ToString();
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            SpawnObjects(addObjectCount);
            objectCountText.text = objectCount.ToString();
        }
    }


    private void SpawnObjects(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            float spawnPositionY = Random.Range(bottomBound, topBound + 1);
            Instantiate(objectToSpawn, new Vector3(leftBound, spawnPositionY, 0), objectToSpawn.transform.rotation, parentObject.transform);
            objectCount++;
        }
    }
}
