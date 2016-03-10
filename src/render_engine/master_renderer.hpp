#pragma once
#include "render_engine/entity_renderer.hpp"
#include "render_engine/terrain_renderer.hpp"
#include "render_engine/loader.hpp"
#include "entities/light.hpp"
#include "entities/camera.hpp"
#include "skybox/skybox_renderer.hpp"
#include <unordered_map>
#include <vector>

class MasterRenderer {
public:
    MasterRenderer(Loader& loader);

    void prepare() const;
    void render(std::vector<Light> const& lights, Camera const& camera);
    void processEntity(Entity const* entity);
    void processTerrain(Terrain const* terrain);

    static void enableCulling();
    static void disableCulling();
    void resetProjectionMatrix();

private:
    using EntityMap = std::unordered_map<TexturedModel const*, std::vector<Entity const*>>;

    glm::mat4 projectionMatrix_;
    StaticShader entityShader_{};
    TerrainShader terrainShader_{};
    EntityRenderer entityRenderer_{&entityShader_};
    TerrainRenderer terrainRenderer_{&terrainShader_};
    EntityMap entities_;
    std::vector<Terrain const*> terrains_;
    SkyboxRenderer skyboxRenderer_;
};