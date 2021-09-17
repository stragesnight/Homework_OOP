#pragma once

#include <string>

#define DBG
#if defined (DBG) && !defined (_DBG_MSG)
# define _DBG_MSG
# include <iostream>
# define dbgmsg(msg) std::cout << "DEBUG: " << msg << '\n'
#endif


enum action_result : int
{
	SUCCESS 	= 0,
	DEAD 		= 1
};


class Entity
{
protected:
	std::string name;

public:
	Entity(const std::string& name)
	{
		set_name(name);
	}

	void set_name(const std::string& name) { this->name = name; }
	const std::string& get_name() { return name; }

	virtual int attack(unsigned dmg)
	{
		std::cout << "* " << name << " attacks! (" << dmg << " damage)\n";
		return dmg;
	}

	virtual int take_damage(unsigned dmg)
	{
		std::cout << "* " << name << " takes " << dmg << " damage!\n";
		return 0;
	}

	virtual int block()
	{
		std::cout << "*  " << name << " blocks!\n";
		return 0;
	}

	virtual void info()
	{
		std::cout << name << "'s info:\n";
	}
};


static const float EXP_MULTIPLIER = 1.1f;

class PhysicalEntity : public Entity
{
protected:
	unsigned lvl;
	unsigned exp_required;
	unsigned exp_curr;
	int health_max;
	int health_curr;

	void level_up()
	{
		lvl++;
		exp_required = float(exp_required) * EXP_MULTIPLIER;
		exp_curr = 0;
		health_max *= EXP_MULTIPLIER;
		health_curr = health_max;

		std::cout << "* LEVEL UP! " << name << " reaches level " << lvl << "!!\n";
		std::cout << "*  health increased to " << health_max << '\n';
		std::cout << "*  " << name << " now needs " << exp_required << " to reach next level!\n";
	}

	void die()
	{
		std::cout << name << " dies in battle...\n";
	}

public:
	PhysicalEntity(const std::string& name, unsigned lvl, int health_max)
		: Entity(name)
	{
		this->lvl = lvl;
		this->exp_curr = 0;
		this->exp_required = lvl * 10 * EXP_MULTIPLIER;
		this->health_max = health_max;
		this->health_curr = health_max;
	}

	int attack(unsigned dmg) override
	{
		exp_curr += dmg;

		if (exp_curr >= exp_required)
			level_up();

		return Entity::attack(dmg * ((rand() & 1) + 1));
	}

	int take_damage(unsigned dmg) override
	{
		Entity::take_damage(dmg);

		exp_curr += dmg / 10;
		health_curr -= dmg;

		if (health_curr <= 0)
		{
			die();
			return DEAD;
		}

		return SUCCESS;
	}

	void heal(unsigned amount)
	{
		std::cout << "* " << name << "'s health is increased by " << amount << "!\n";
		health_curr += amount;
		if (health_curr > health_max)
			health_curr = health_max;
	}

	int block() override
	{
		return Entity::block();
	}

	void info() override
	{
		Entity::info();
		std::cout << " lvl: " << lvl << '\n';
		std::cout << " exp: " << exp_curr << '/' << exp_required << '\n';
		std::cout << " health: " << health_curr << '/' << health_max << "\n\n";
	}
};

