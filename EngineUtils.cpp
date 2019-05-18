//
// Created by jordan on 5/16/19.
//

#include "EngineUtils.h"
#include <memory>

/**
 * Determine if the game object is of the template type.
 *
 * @tparam T The type to check go against.
 * @param go The game object to determine if the type matches.
 * @return True if the game object is the same, false otherwise.
 */
template <typename T>
bool isType(std::shared_ptr<GameObject> go)
{
    std::shared_ptr<T> tmp = std::dynamic_pointer_cast<T>(go);
    return tmp != nullptr;
}


/**
 * Find al functions by their tag. This is likely way more efficiant than finding them by their type, however
 * the user can make the tag of an object anything they want.
 *
 * @param gameObjects The game objects to search through
 * @return A list of matching game objects. This list will be empty if none are found.
 */
std::list<std::shared_ptr<GameObject>> FindAllByTag(std::list<std::shared_ptr<GameObject>> gameObjects)
{
    std::list<std::shared_ptr<GameObject>> matches;
    for (auto const &go : gameObjects)
    {
        matches.emplace_back(go);
    }

    return matches;
}