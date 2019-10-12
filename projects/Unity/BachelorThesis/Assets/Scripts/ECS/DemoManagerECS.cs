using UnityEngine;
using UnityEngine.UI;
using Unity.Entities;
using Unity.Transforms;
using Unity.Mathematics;
using Unity.Collections;
using Unity.Rendering;
using System.Collections;
using System.Collections.Generic;

public class DemoManagerECS : MonoBehaviour
{
    [SerializeField] public static float leftBound = -103.0f;
    [SerializeField] public static float rightBound = 103.0f;

    [SerializeField] public static float topBound = 55.0f;
    [SerializeField] public static float bottomBound = -55.0f;
    [SerializeField] private int initialObjectCount;
    [SerializeField] private int addObjectCount;
    [SerializeField] private GameObject Prefab;
    [SerializeField] private Mesh entityMesh;
    [SerializeField] private Material blueprintMaterial;

    [SerializeField] private bool changeColor;
    [SerializeField] private bool avoidPredator;

    public static Entity predator;

    [SerializeField] Text objectCountText;
    private int objectCount = 0;

    private Entity prefab;
    private EntityManager entityManager;

    private void Start()
    {
        prefab = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);
        entityManager = World.Active.EntityManager;

        SpawnObjects(initialObjectCount);
        objectCountText.text = objectCount.ToString();

        NativeArray<Entity> entities = entityManager.GetAllEntities();
        for (int i = 0; i < entities.Length; i++)
        {
            if (entityManager.HasComponent<PredatorComponent>(entities[i]))
            {
                predator = entities[i];
                break;
            }
        }
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
        NativeArray<Entity> entities = new NativeArray<Entity>(amount, Allocator.Temp);
        entityManager.Instantiate(prefab, entities);

        for (int i = 0; i < amount; i++)
        {
            if (avoidPredator)
            {
                entityManager.AddComponent<AvoidPredatorComponent>(entities[i]);
                entityManager.SetComponentData(entities[i], new AvoidPredatorComponent { avoiding = false, avoidingUp = false });
            }            
            
            entityManager.AddComponent<MovementSpeed>(entities[i]);
            entityManager.SetComponentData(entities[i], new MovementSpeed { Value = UnityEngine.Random.Range(2.0f, 10.0f) });

            float spawnPositionY = UnityEngine.Random.Range(bottomBound, topBound + 1);
            Vector3 position = transform.TransformPoint(new float3(leftBound, spawnPositionY, 0));
            entityManager.SetComponentData(entities[i], new Translation { Value = position });            

            if (changeColor)
            {
                entityManager.AddComponent<ColorChangeComponent>(entities[i]);
                Material randomMaterial = new Material(blueprintMaterial);
                randomMaterial.SetColor("_Color", UnityEngine.Random.ColorHSV());

                entityManager.SetSharedComponentData(entities[i], new RenderMesh
                {
                    mesh = entityMesh,
                    material = randomMaterial
                });
            }
            
            objectCount++;
        }

        entities.Dispose();
    }
}
