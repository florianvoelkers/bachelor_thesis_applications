using UnityEngine;
using Unity.Entities;
using Unity.Transforms;
using Unity.Mathematics;

public class MovementSystem : ComponentSystem
{
    protected override void OnUpdate()
    {
        Entities.ForEach((ref Translation translation, ref MovementSpeed movementSpeed) =>
        {
            if (movementSpeed.Value > 0.0f)
            {
                if (translation.Value.x < DemoManagerECS.rightBound)
                {
                    float spawnPositionY = UnityEngine.Random.Range(DemoManagerECS.bottomBound, DemoManagerECS.topBound + 1);
                    translation.Value.x += movementSpeed.Value * Time.deltaTime;
                    
                }
                else
                {
                    float spawnPositionY = UnityEngine.Random.Range(DemoManagerECS.bottomBound, DemoManagerECS.topBound + 1);
                    translation.Value.x = DemoManagerECS.leftBound;
                    translation.Value.y = spawnPositionY;
                }
            }
            else
            {
                if (translation.Value.x > DemoManagerECS.leftBound)
                {                    
                    translation.Value.x += movementSpeed.Value * Time.deltaTime;
                }
                else
                {
                    float spawnPositionY = UnityEngine.Random.Range(DemoManagerECS.bottomBound, DemoManagerECS.topBound + 1);
                    translation.Value.x = DemoManagerECS.rightBound;
                    translation.Value.y = spawnPositionY;
                }
            }
        });
    }
}
