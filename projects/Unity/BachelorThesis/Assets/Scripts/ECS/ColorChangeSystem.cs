using UnityEngine;
using Unity.Entities;
using Unity.Transforms;
using Unity.Mathematics;
using Unity.Rendering;

public class ColorChangeSystem : ComponentSystem
{
    protected override void OnUpdate()
    {
        float deltaTime = Time.deltaTime;

        Entities.WithAll<RenderMesh, ColorChangeComponent>().ForEach((Entity e) =>
        {
            RenderMesh renderMesh = EntityManager.GetSharedComponentData<RenderMesh>(e);

            Color oldColor = renderMesh.material.GetColor("_Color");
            float newR = oldColor.r + deltaTime;
            float newG = oldColor.g + deltaTime;
            float newB = oldColor.b + deltaTime;
            if (newR > 1.0f)
                newR = 0.0f;
            if (newG > 1.0f)
                newG = 0.0f;
            if (newB > 1.0f)
                newB = 0.0f;

            renderMesh.material.SetColor("_Color", new Color(newR, newG, newB, oldColor.a));
        });
    }
}