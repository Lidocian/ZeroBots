#include "botpch.h"
#include "../../playerbot.h"
#include "FeralDruidStrategy.h"

using namespace ai;

class FeralDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FeralDruidStrategyActionNodeFactory()
    {
        creators["thorns"] = &thorns;
        creators["cure poison"] = &cure_poison;
        creators["cure poison on party"] = &cure_poison_on_party;
        creators["abolish poison"] = &abolish_poison;
        creators["abolish poison on party"] = &abolish_poison_on_party;
		creators["prowl"] = &prowl;
    }
private:
    static ActionNode* thorns(PlayerbotAI* ai)
    {
        return new ActionNode ("thorns",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
	static ActionNode* prowl(PlayerbotAI* ai)
	{
		return new ActionNode("prowl",
			/*P*/ NextAction::array(0, new NextAction("cat form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
};

FeralDruidStrategy::FeralDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new FeralDruidStrategyActionNodeFactory());
    actionNodeFactories.Add(new ShapeshiftDruidStrategyActionNodeFactory());
}

void FeralDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_NORMAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_NORMAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("dire bear form", ACTION_EMERGENCY + 2), new NextAction("frenzied regeneration", ACTION_EMERGENCY + 1), NULL)));
	
}

