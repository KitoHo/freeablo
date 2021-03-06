#include "monster.h"

#include <diabloexe/monster.h>

#include "../falevelgen/random.h"
#include "../engine/threadmanager.h"

#include "world.h"

#include <boost/format.hpp>

namespace FAWorld
{
    STATIC_HANDLE_NET_OBJECT_IN_IMPL(Monster)

    void Monster::init()
    {
        mAnimTimeMap[AnimState::dead] = FAWorld::World::getTicksInPeriod(0.1);
        mAnimTimeMap[AnimState::idle] = FAWorld::World::getTicksInPeriod(0.1);
        mAnimTimeMap[AnimState::dead] = FAWorld::World::getTicksInPeriod(0.1);
        mAnimTimeMap[AnimState::hit] = FAWorld::World::getTicksInPeriod(0.1);

        mIsEnemy = true;
    }

    Monster::Monster()
    {
        init();
    }

    Monster::Monster(const DiabloExe::Monster& monster, Position pos, ActorStats *stats):
        Actor("", "", pos, "", stats), mAnimPath(monster.cl2Path), mSoundPath(monster.soundPath)
    {
        init();

        boost::format fmt(mAnimPath); 
        mWalkAnim = FARender::Renderer::get()->loadImage((fmt % 'w').str());
        mIdleAnim = FARender::Renderer::get()->loadImage((fmt % 'n').str());
        mDieAnim =  FARender::Renderer::get()->loadImage((fmt % 'd').str());
        mHitAnim =  FARender::Renderer::get()->loadImage((fmt % 'h').str());
    }

    std::string Monster::getDieWav()
    {
        boost::format fmt(mSoundPath);
        fmt % 'd';
        return (fmt % FALevelGen::randomInRange(1, 2)).str();

    }

    std::string Monster::getHitWav()
    {
        if(mSoundPath.empty())
        {
            printf("No sound for caller\n");
            return "";
        }
        else
        {
            boost::format fmt(mSoundPath);
            fmt % 'h';
            return (fmt % FALevelGen::randomInRange(1, 2)).str();
        }
    }
}
