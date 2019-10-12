using System;
using Unity.Entities;
using Unity.Mathematics;
using UnityEngine;

[RequiresEntityConversion]
public class MovementSpeedAuthoring : MonoBehaviour, IConvertGameObjectToEntity
{
    public float speed;

    public void Convert(Entity entity, EntityManager dstManager, GameObjectConversionSystem conversionSystem)
    {
        var data = new MovementSpeed { Value = speed };
        dstManager.AddComponentData(entity, data);
    }
}