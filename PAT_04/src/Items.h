#include "Entity.h"


class Item : public PhysicalEntity
{
protected:
	PhysicalEntity* owner;

public:
	Item(const std::string& name, PhysicalEntity*& owner)
		: PhysicalEntity(owner->get_name(), 9999, 9999)
	{
		std::cout << name << " recieved!\n";
		this->owner = owner;
		owner = this;
	}

	~Item()
	{
		delete owner;
	}

	void info() override
	{
		owner->info();
	}
};

class HealingPotion : public Item
{
public:
	HealingPotion(PhysicalEntity*& owner)
		: Item("Healing potion", owner)
	{
		std::cout << "it heals the owner while blocking\n\n";
	}

	int block() override
	{
		owner->heal(5);
		return owner->block();
	}
};

class SharpeningStone : public Item
{
public:
	SharpeningStone(PhysicalEntity*& owner)
		: Item("Sharpening stone", owner)
	{
		std::cout << "it slightly increases damage\n\n";
	}

	int attack(unsigned dmg) override
	{
		return owner->attack(dmg + 2);
	}
};

class PoisonOil : public Item
{
public:
	PoisonOil(PhysicalEntity*& owner)
		: Item("Poison oil", owner)
	{
		std::cout << "it greatly increases damage\n\n";
	}

	int attack(unsigned dmg) override
	{
		return owner->attack(dmg + (rand() & 0b111));
	}
};

class Shield : public Item
{
public:
	Shield(PhysicalEntity*& owner)
		: Item("Shield", owner)
	{
		std::cout << "it greatly reduces recieved damage\n\n";
	}

	int take_damage(unsigned dmg) override
	{
		return owner->take_damage(dmg / 2);
	}
};

class BlindingBomb : public Item
{
public:
	BlindingBomb(PhysicalEntity*& owner)
		: Item("Shield", owner)
	{
		std::cout << "owner now has a chance to blind attacking enemy\n\n";
	}

	int take_damage(unsigned dmg) override
	{
		if (rand() % 6 == 0)
			return owner->take_damage(dmg);
		else
		{
			std::cout << "* " << owner->get_name() 
				<< " throws blinding bomb! enemy attack ignored";
			return SUCCESS;
		}
	}
};

