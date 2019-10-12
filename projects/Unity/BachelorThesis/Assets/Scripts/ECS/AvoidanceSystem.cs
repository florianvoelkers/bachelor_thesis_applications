using UnityEngine;
using Unity.Entities;
using Unity.Transforms;
using Unity.Mathematics;

public class AvoidanceSystem : ComponentSystem
{
    float avoidDistanceX = 8.0f;
    float avoidDistanceY = 5.0f;

    protected override void OnUpdate()
    {
        Translation predatorTranslation = EntityManager.GetComponentData<Translation>(DemoManagerECS.predator);        
        Entities.ForEach((ref Translation translation, ref AvoidPredatorComponent avoidPredator) =>
        {
            float actualDistanceX = math.abs(translation.Value.x - predatorTranslation.Value.x);
            float actualDistanceY = translation.Value.y - predatorTranslation.Value.y;
            if (actualDistanceX < avoidDistanceX && math.abs(actualDistanceY) < avoidDistanceY)
            {
                avoidPredator.avoiding = true;
                if (actualDistanceY >= 0.0f)
                {
                    translation.Value.y += avoidDistanceY;
                    avoidPredator.avoidingUp = true;
                }
                else
                {
                    translation.Value.y -= avoidDistanceY;
                    avoidPredator.avoidingUp = false;
                }
            }

            if (actualDistanceX > avoidDistanceX && math.abs(actualDistanceY) < avoidDistanceY * 2 && avoidPredator.avoiding)
            {
                if (avoidPredator.avoidingUp)
                    translation.Value.y -= avoidDistanceY;
                else
                    translation.Value.y += avoidDistanceY;

                avoidPredator.avoiding = false;
            }
        });
    }
}
