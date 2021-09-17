#pragma once

#include "Entity.h"
#include "Items.h"
#include "UserInterface.h"

#define DBG
#if defined (DBG) && !defined (_DBG_MSG)
# define _DBG_MSG
# include <iostream>
# define dbgmsg(msg) std::cout << "DEBUG: " << msg << '\n'
#endif

#include <chrono>
#include <thread>
#include <ctime>

class GameManager;
static GameManager* instance = nullptr;

class GameManager
{
private:
	UserInterfaceAbstraction* ui;
	PhysicalEntity* player;
	PhysicalEntity* enemy = nullptr;

	bool players_turn = false;

	GameManager()
	{
		this->player = new PhysicalEntity("player", 1, 20);

		this->ui = new UserInterfaceAbstraction(
# 				if defined (__linux__)
					new LinuxUserInterface()
# 				elif defined (_WIN32) or defined (_WIN64)
					new WindowsUserInterface()
# 				endif
				);

		srand(time(0));
	}

	void handle_players_turn()
	{
		int decision = 0;

		std::cout << "it's your turn! make your decision:\n";
		std::cout << "1. attack\n";
		std::cout << "2. block\n";
		std::cout << "3. view player info\n";
		std::cout << "4. view enemy info (and waste turn)\n";
		std::cout << "0. surrender\n\n";
		std::cout << "your choice: ";
		std::cin >> decision;

		switch (decision)
		{
		case 1:
			if (enemy->take_damage(player->attack(1)) == DEAD)
				end_battle(enemy);
			break;
		case 2:
			player->block();
			break;
		case 3:
			player->info();
			handle_players_turn();
			break;
		case 4:
			enemy->info();
			break;
		case 0:
			std::cout << "player surrenders!\n";
			end_battle(player);
			break;
		default:
			std::cout << "invalid decision!\n";
			break;
		}
	}

	void handle_enemy_turn()
	{
		std::cout << "* enemy makes his decision...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		int decision = rand() % 1;

		switch (decision)
		{
		case 0:
			if (player->take_damage(enemy->attack(1)) == DEAD)
				end_battle(player);
			break;
		case 1:
			enemy->block();
			break;
		default:
			dbgmsg("invalid decision");
			break;
		}
	}

	void give_random_item(PhysicalEntity*& entity)
	{
		int item = rand() % 5;

		switch (item)
		{
		case 0:
		{
			HealingPotion* tmp = new HealingPotion(entity);
			break;
		}
		case 1:
		{
			SharpeningStone* tmp = new SharpeningStone(entity);
			break;
		}
		case 2:
		{
			PoisonOil* tmp = new PoisonOil(entity);
			break;
		}
		case 3:
		{
			Shield* tmp = new Shield(entity);
			break;
		}
		case 4:
		{
			BlindingBomb* tmp = new BlindingBomb(entity);
			break;
		}
		default:
			return;
		}
	}

public:
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;

	static GameManager* get_instance() 
	{
		if (instance == nullptr)
			instance = new GameManager();

		return instance;
	}

	void start_battle()
	{
		if (enemy != nullptr)
			delete enemy;

		std::cout << "your enemy is preparing...\n\n";
		enemy = new PhysicalEntity("enemy", rand() & 0b11, (rand() & 0b11) * 10);

		for (int i = 0; i < (rand() & 0b11); i++)
			give_random_item(enemy);

		enemy->info();

		players_turn = rand() & 1;
		while (true)
			switch_turn();
	}

	void end_battle(Entity* loser)
	{
		ui->clear_screen();

		if (player == loser)
		{
			std::cout << "=========================\n";
			std::cout << "||     GAME   OVER     ||\n";
			std::cout << "=========================\n\n";
			exit(0);
		}
		else
		{
			delete enemy;
			enemy = nullptr;

			std::cout << "=========================\n";
			std::cout << "||      YOU   WON      ||\n";
			std::cout << "=========================\n\n";

			std::cout << "you found something on the ground...\n";
			give_random_item(player);

			std::cout << "1. proceed to the next battle\n";
			std::cout << "2. leave arena (exit program)\n\n";
			std::cout << "your choice: ";

			if (getchar() == 1)
				start_battle();
			exit(0);
		}
	}

	void switch_turn()
	{
		players_turn = !players_turn;

		if (players_turn)
		{
			std::cout << "\n\nit is your turn now!\n\n";
			handle_players_turn();
		}
		else
		{
			std::cout << "\n\nit is enemy\'s turn now!\n\n";
			handle_enemy_turn();
		}
	}
};

