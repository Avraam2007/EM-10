#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

class Gamer;

int betterRandomizer(int min, int max) {
	if (min > max) {
		swap(min, max);
	};
	return min + rand() % (max - min + 1);;
};




class Name {
private:
protected:
	string name = "";
public:
	Name(string name) {
		this->name = name;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() { return this->name; }

	~Name() { }
};

class Shield : public Name {
private:
protected:
	int protect = 0;
	int price = 0;
public:
	Shield(int protect, int price, string name) : Name(name) {
		this->setName(name);
	}
	void setProtect(int protect) {
		this->protect = protect;
	}

	void setPrice(int price) {
		this->price = price;
	}

	int getPrice() { return this->price; }

	int getProtect() { return this->protect; }

	~Shield() { }
};

class Weapon : public Name {
private:
protected:
	int damage = 0;
	int price = 0;
public:
	Weapon(int damage, int price, string name) : Name(name) {
		this->setName(name);
	}

	void setDamage(int damage) {
		this->damage = damage;
	}

	void setPrice(int price) {
		this->price = price;
	}

	int getPrice() { return this->price; }

	int getDamage() { return this->damage; }

	~Weapon() { }
};

class Person : public Name {
private:
protected:
	int health = 0;
	int energy = 0;
	int level = 0;
	int money = 0;
public:
	Person(int health, int energy, int level, string name) : Name(name) {
		this->health = health;
		this->energy = energy;
		this->level = level;
		this->name = name;
	}
	void setHealth(int health) {
		this->health = health;
	}

	void setEnergy(int energy) {
		this->energy = energy;
	}
	void setLevel(int level) {
		this->level = level;
	}

	void setName(string name) {
		this->name = name;
	}

	int getHealth() { return this->health; }

	int getEnergy() { return this->energy; }

	int getLevel() { return this->level; }

	string getName() { return this->name; }


	~Person() { }
};

class SkillInterface : public Name {
private:

protected:
public:
	SkillInterface(string name) : Name(name) { }

	virtual void useSkill(Gamer* player) = 0;
	virtual void printName() = 0;

	~SkillInterface() { }
};

class Healing : public SkillInterface {
public:
protected:
public:
	Healing() : SkillInterface(name) { }

	void useSkill(Gamer* player) override {
		while (player->getHealth() < player->getMaxHealth()) {
			player->setHealth(player->getHealth() + betterRandomizer(0, 10));
		}
	};

	void printName() override {}

	~Healing() { }
};

class CriticalDamage : public SkillInterface {
public:
protected:
public:
	CriticalDamage() : SkillInterface(name) { }

	void useSkill(Gamer* player) override {
		if (player->getWeapon() != NULL) {
			player->setDamage(player->getDamage() + player->getWeapon()->getDamage() + player->getPower() % 100 + (player->getAgility() % 10));
		}
		else {
			player->setDamage(player->getDamage() + player->getPower() % 100 + (player->getAgility() % 10));
		}

	}
	void printName() override {}
	~CriticalDamage() { }
};

class LevelUp : public SkillInterface {
public:
protected:
public:
	LevelUp() : SkillInterface(name) { }

	void useSkill(Gamer* player) override {
		player->setLevel(player->getLevel() + 1);
	}

	void printName() override {}

	~LevelUp() { }
};

class PotionInterface : public Name{
private:
protected:
public:
	PotionInterface(string name) : Name(name) { }

	virtual void usePotion(Gamer* player) = 0;

	~PotionInterface() { }
};

class DamagePotion : public PotionInterface {
private:
	int price = 0;
	int plusDamage = 0;
protected:
public:
	DamagePotion(int price, int plusDamage, string name) : PotionInterface(name) {
		this->price = price;
		this->plusDamage = plusDamage;
	}

	void setPrice(int price) {
		this->price = price;
	}

	void setDamage(int plusDamage) {
		this->plusDamage = plusDamage;
	}

	int getPlusDamage() {
		return this->plusDamage;
	}


	int getPrice() {
		return this->price;
	}

	void usePotion(Gamer* player) override {
		player->setDamage(player->getDamage() + 50);
		cout << "I`m drink damage potion. Damage = " << player->getDamage() << endl;
	}
	~DamagePotion() { }
};

class EnergyPotion : public PotionInterface {
private:
	int price = 0;
	int plusEnergy = 0;
protected:
public:
	EnergyPotion(int price, int plusEnergy, string name) : PotionInterface(name) {
		this->price = price;
		this->plusEnergy = plusEnergy;
	}

	void setPrice(int price) {
		this->price = price;
	}

	void setplusEnergy(int plusEnergy) {
		this->plusEnergy = plusEnergy;
	}

	int getPlusEnergy() {
		return this->plusEnergy;
	}


	int getPrice() {
		return this->price;
	}


	void usePotion(Gamer* player) override {
		player->setEnergy(player->getEnergy() + getPlusEnergy());
		cout << "I`m drink energy potion. Energy = " << player->getEnergy() << endl;
	}

	~EnergyPotion() { }
};

class XpPotion : public PotionInterface {
private:
	int price = 0;
	int plusXp = 0;
protected:
public:
	XpPotion(int price, int plusXp, string name) : PotionInterface(name) {
		this->price = price;
		this->plusXp = plusXp;
	}

	void setPrice(int price) {
		this->price = price;
	}

	void setPlusXp(int plusDamage) {
		this->plusXp = plusXp;
	}

	int getPlusXp() {
		return this->plusXp;
	}


	int getPrice() {
		return this->price;
	}

	void usePotion(Gamer* player) override {
		player->setXp(player->getXp() + getPlusXp());
		cout << "I`m drink xp potion. XP = " << player->getXp() << endl;
	}

	~XpPotion() { }
};

class Gamer : public Person {
private:
protected:
	int power = 0;
	int agility = 0;
	int endurance = 0;
	int xp = 0;
	int damage = 0;
	int protect = 0;
	int wallet = 0;
	int maxHealth = 0;
	Shield* panel = NULL;
	Weapon* armament = NULL;
	vector<SkillInterface*> skills;
	PotionInterface* potion;

public:
	Gamer(int health, int maxHealth, int energy, int power, int agility, int endurance, int level, int xp, int wallet, string name) : Person(health, energy, level, name) {
		this->power = power;
		this->agility = agility;
		this->endurance = endurance;
		this->xp = xp;
	}

	~Gamer() { }

	//----------------------------------------//
	bool addedSkill(SkillInterface* skill) {
		if (skills.size() < 3) {
			skills.push_back(skill);
			return true;
		}

		cout << "Error!!!!";
		return false;
	}

	bool changeSkill(int position, SkillInterface* skill) {
		if (position >= 0 && position < skills.size()) {
			cout << "Error!!!!";
			return false;
		}

		skills[position] = skill;
		return true;
	}

	bool useSkill(int position) {
		if (position >= 0 && position < skills.size()) {
			cout << "Error!!!!";
			return false;
		}

		skills[position]->useSkill(this);

		return true;
	}

	void showSkillList() {
		for (int i = 0; i < skills.size(); i++) {
			cout << i + 1 << " ";
			skills[i]->printName();
			cout << endl;
		}
	}
	//----------------------------------------//
	//----------------------------------//
	void setPotion(PotionInterface* pi) {
		this->potion = pi;
	}

	bool usePotion() {
		if (this->potion == NULL) {
			cout << "Error!!!!";
			return false;
		}

		this->potion->usePotion(this);
		this->potion = NULL;

		return true;
	}
	//----------------------------------//

	void setWeapon(Weapon* armament) {
		this->armament = armament;
	}

	void setShield(Shield* panel) {
		this->panel = panel;
	}

	void setXp(int xp) {
		this->xp = xp;
	}

	void setPower(int power) {
		this->power = power;
	}
	void setAgility(int agility) {
		this->agility = agility;
	}

	void setEndurance(int endurance) {
		this->endurance = endurance;
	}

	void setWallet(int wallet) {
		this->wallet = wallet;
	}

	void setMaxHealth(int maxHealth) {
		this->maxHealth = maxHealth;
	}

	void setDamage(int damage) {
		this->damage = armament->getDamage() + damage;
	}

	void setProtect(int protect) {
		this->protect = protect + armament->getDamage() + this->endurance % 100;
	}

	int getXp() { return this->xp; }

	Weapon* getWeapon() { return this->armament; }

	Shield* getShield() { return this->panel; }

	int getPower() { return this->power; }

	int getAgility() { return this->agility; }

	int getEndurance() { return this->endurance; }

	int getMaxHealth() { return this->maxHealth; }

	int getDamage() { return this->damage; }

	int getProtect() { return this->protect; }

	int getWallet() { return this->wallet; }

};





class Monster : public Person {
private:
protected:
	int damage = 0;
	int protect = 0;
	int xpPlus = 0;
public:
	Monster(int health, int energy, int damage, int protect, int level, int xpPlus, string name) : Person(health, energy, level, name) {
		this->damage = damage;
		this->protect = protect;
		this->xpPlus = xpPlus;
	}

	void setHealth(int health) {
		this->health = health;
	}

	void setMonsterLevel(int level) {
		this->level = level + betterRandomizer(0 - this->level, 1);
	}

	void setEnergy(int energy) {
		this->energy = energy;
	}
	void setLevel(int level) {
		this->level = level;
	}

	void setName(string name) {
		this->name = name;
	}

	void setDamage(int damage) {
		this->damage = damage;
	}

	void setProtect(int protect) {
		this->protect = protect;
	}

	void setXpPlus(int xpPlus) {
		this->xpPlus = xpPlus;
	}

	void setMonsterMoney(int money) {
		this->money = money + rand() % getLevel();
	}

	int getHealth() { return this->health; }

	int getEnergy() { return this->energy; }

	int getMonsterLevel() { return this->level; }

	string getName() { return this->name; }

	int getDamage() { return this->damage; }

	int getProtect() { return this->protect; }

	int getXpPlus() { return this->xpPlus; }

	~Monster() { }
};

class SaveLoad {
private:
	Gamer* player = NULL;
protected:
public:
	SaveLoad(Gamer* player) {
		this->player = player;
	}

	auto savePlayer() {
		ofstream save;

		save.open("PlayerData.txt");
		save.write((char*)&player, sizeof(Gamer));
		save.close();
	}

	Gamer* loadPlayer() {
		ifstream load;

		Gamer* person = NULL;
		load.open("PlayerData.txt");
		load.read((char*)&person, sizeof(Gamer));
		load.close();

		return person;
	}

	Gamer* getGamerData() {
		return player;
	}

	~SaveLoad() { }
};

class Engine {
private:
	string list[10] = { "Ð¡yclop", "Minotaur", "Phobos", "Toxic student", "Orc", "Elf", "Wizzard", "Illager", "Skeleton", "Necrophos" };
	SaveLoad* role = NULL;
public:
	Engine() { }

	SkillInterface* createSkillInterface(int choose) {
		SkillInterface* sinter = NULL;

		if (choose < 1 || choose > 3) {
			cerr << "\a Wrong value of function setSkillInterface()! Try again!";
		}
		else if (choose == 1) {
			sinter = new Healing();
		}
		else if (choose == 2) {
			sinter = new CriticalDamage();
		}
		else {
			sinter = new LevelUp();
		}

		return sinter;
	}


	auto createPotionInterface(int choose) {
		PotionInterface* pi = NULL;
		DamagePotion* di = NULL;
		EnergyPotion* ei = NULL;
		XpPotion* xi = NULL;

		if (choose < 1 || choose > 3) {
			cerr << "\a Wrong value of function setPotionInterface()! Try again!";
		}
		else if (choose == 1) {
			pi = new EnergyPotion(ei->getPrice(), ei->getPlusEnergy(), "Energy Potion");
		}
		else if (choose == 2) {
			pi = new DamagePotion(di->getPrice(), di->getPlusDamage(), "Damage Potion");
		}
		else {
			pi = new XpPotion(xi->getPrice(), xi->getPlusXp(), "Xp Potion");
		}

		return pi;
	}

	auto typeName(string text) {
		cout << text;
		cin >> text;
		return text;
	}

	int typeNameInt(string text) {
		int number = 0;
		cout << text;
		cin >> number;
		return number;
	}

	Monster* createMonster(int level) {
		return new Monster(rand() % 1000, rand() % 500, rand() % 10, rand() % 100, level, rand() % 50, this->list[rand()]);
	}

	Gamer* createGamer(string name, string choose) {
		Gamer* player = NULL;

		if (choose == "barbar") {
			//player = new Barbar(1000, 500, 100, 20, 300, 1, 200, typeName("Enter your name: "));
			player = new Gamer(1000, 1000, 500, 150, 20, 300, 1, 200, 100, name);
		}
		else if (choose == "tank") {
			//player = new Tank(1100, 500, 100, 20, 300, 1, 200, typeName("Enter your name: "));
			player = new Gamer(1100, 1100, 500, 100, 20, 350, 1, 200, 100, name);
		}
		else if (choose == "murder") {
			//player = new Murder(900, 500, 100, 20, 300, 1, 200, typeName("Enter your name: "));
			player = new Gamer(900, 900, 500, 100, 70, 300, 1, 200, 100, name);
		}

		player->addedSkill(this->createSkillInterface(1));

		player->setPotion(this->createPotionInterface(1));

		return player;
	}

	Weapon* createWeapon(int choose2) {
		string names[7] = { "flint and stone","sword","bow","fireball","axe","AK-47","HIPL" };
		int armors[7] = { 3,5,7,9,11,15,20 };
		int prices[7] = { 30,50,70,90,110,150,200 };

		return new Weapon(armors[choose2 - 1], prices[choose2 - 1], names[choose2 - 1]);
	}

	Shield* createShield(int choose2) {
		string names[7] = { "package ATB","wood","stone","steel","IRIS","graphene","magic shield" };
		int armors[7] = { 3,5,7,9,11,15,20 };
		int prices[7] = { 30,50,70,90,110,150,200 };

		return new Shield(armors[choose2 - 1], prices[choose2 - 1], names[choose2 - 1]);
	}

	~Engine() { }
};

class Event {
private:
	string list[10] = { "Ð¡yclop", "Minotaur", "Phobos", "Toxic student", "Orc", "Elf", "Wizzard", "Illager", "Skeleton", "Necrophos" };
	int minus = 0;
	Gamer* player = NULL;
	Monster* enemy = NULL;

	Weapon* buyWeapon(int wallet, int damage, int price, string name) {

		if (checkWallet(price, wallet)) {
			return new Weapon(damage, price, name);
		}

		return NULL;
	}

	Shield* buyShield(int wallet, int protect, int price, string name) {

		if (checkWallet(price, wallet)) {
			return new Shield(protect, price, name);
		}

		return NULL;
	}

	XpPotion* buyXpPotion(int wallet,int price, int plusXp, string name) {

		if (checkWallet(price, wallet)) {
			return new XpPotion(price, plusXp, name);
		}

		return NULL;
	}

	DamagePotion* buyDamagePotion(int wallet, int price, int plusDamage, string name) {

		if (checkWallet(price, wallet)) {
			return new DamagePotion(price, plusDamage, name);
		}

		return NULL;
	}

	EnergyPotion* buyEnergyPotion(int wallet, int price, int plusEnergy, string name) {

		if (checkWallet(price, wallet)) {
			return new EnergyPotion(price, plusEnergy, name);
		}

		return NULL;
	}



public:
	Event(Gamer* player) {
		this->player = player;
	}

	auto typeName(string text) {
		cout << text;
		cin >> text;
		return text;
	}

	int typeNameInt(string text) {
		int number = 0;
		cout << text;
		cin >> number;
		return number;
	}

	bool checkWallet(int price, int wallet) {
		if (price > wallet) {
			cout << "Sorry, we can't give credit! Come back when you been little mmm..... Richer!";
			return false;
		}
		else {
			this->player->setWallet(wallet - price);
			return true;
		}
	}


	Weapon* shopWeapon(int choose3) {
		Weapon* gun = NULL;
		int wallet = player->getWallet();

		switch (choose3) {
		case 1:
			return this->buyWeapon(wallet, 3, 30, "flint and stone");
			break;
		case 2:
			return this->buyWeapon(wallet, 5, 50, "sword");
			break;
		case 3:
			return this->buyWeapon(wallet, 7, 70, "bow");
			break;
		case 4:
			return this->buyWeapon(wallet, 9, 90, "fireball");
			break;
		case 5:
			return this->buyWeapon(wallet, 11, 110, "axe");
			break;
		case 6:
			return this->buyWeapon(wallet, 15, 150, "AK-47");
			break;
		case 7:
			return this->buyWeapon(wallet, 20, 200, "HIPL");
			break;
		default:
			cerr << "\aError: Wrong value! Try again!";
			return NULL;
			break;
		}

	}

	Shield* shopShield(int choose3) {
		Shield* target = NULL;
		int wallet = player->getWallet();

		switch (choose3) {
		case 1:
			return this->buyShield(wallet, 3, 30, "package ATB");
			break;
		case 2:
			return this->buyShield(wallet, 5, 50, "wood");
			break;
		case 3:
			return this->buyShield(wallet, 7, 70, "stone");
			break;
		case 4:
			return this->buyShield(wallet, 9, 90, "steel");
			break;
		case 5:
			return this->buyShield(wallet, 11, 110, "IRIS");
			break;
		case 6:
			return this->buyShield(wallet, 15, 150, "graphene");
			break;
		case 7:
			return this->buyShield(wallet, 20, 200, "magic shield");
			break;
		default:
			cerr << "\aError: Wrong value! Try again!";
			return NULL;
			break;
		}
	}

	PotionInterface* shopPotion(int choose3) {
		PotionInterface* potion = NULL;
		int wallet = player->getWallet();

		switch (choose3) {
		case 1:
			return this->buyXpPotion(wallet, 100, 100, "+100 Xp Potion");
			break;
		case 2:
			return this->buyXpPotion(wallet, 200, 200, "+200 Xp Potion");
			break;
		case 3:
			return this->buyDamagePotion(wallet, 100, 100, "+100 Damage Potion");
			break;
		case 4:
			return this->buyDamagePotion(wallet, 200, 200, "+200 Damage Potion");
			break;
		case 5:
			return this->buyEnergyPotion(wallet, 100, 100, "+100 Energy Potion");
			break;
		case 6:
			return this->buyEnergyPotion(wallet, 200, 200, "+200 Energy Potion");
			break;
		default:
			cerr << "\aError: Wrong value! Try again!";
			return NULL;
			break;
		}
	}

	auto mainPage(int choose) {
		if (choose == 1) {
			this->player->setWeapon(shopWeapon(typeNameInt("Choose item: \n1-flint and stone-30$ \n2-sword-50$ \n3-bow-70$ \n4-fireball-90$ \n5-axe-110$ \n6-AK-47-150$ \n7-HIPL-200$")));
		}
		else if (choose == 2) {
			this->player->setShield(shopShield(typeNameInt("Choose item: \n1-package ATB-30$ \n2-wood-50$ \n3-stone-70$ \n4-steel-90$ \n5-IRIS-110$ \n6-graphene-150$ \n7-magic shield-200$(SALE -0,0000001%!!!)")));
		}
		else if (choose == 3) {
			shopPotion(typeNameInt("Choose item: \n1-+100-100$ \n2-wood-2000$ \n3-stone-100$ \n4-steel-200$ \n5-IRIS-100$ \n6-graphene-200$"));
		}
		else if (choose == 4) {
			cout << "OK";
		}
		else {
			cerr << "\aError: Wrong value! Try again!";
			return 0;
		};
	}

	auto meetMonster() {
		int choose = typeNameInt("Do you want to drink potion(1-yes,2-no)");
		if (choose < 1 || choose > 2) {
			cerr << "\aError: Wrong value! Try again!";
			return 0;
		}
		else if (choose == 1) {
			player->usePotion();
		}
		else {
			cout << "OK!";
		}
		int skillChoose = typeNameInt("Do you want to use skill(1-level up,2-critical damage,3-healing,4-no)");
		if (choose < 1 || choose > 4) {
			cerr << "\aError: Wrong value! Try again!";
			return 0;
		}
		else if (choose == 1) {
			player->useSkill(1);
		}
		else if (choose == 2) {
			player->useSkill(2);
		}
		else if (choose == 3) {
			player->useSkill(3);
		}
		else {
			cout << "OK!";
		}
		Engine* action = new Engine();
		this->enemy = action->createMonster(this->player->getLevel());


		cout << "Monster has spawned!";

		int roundCount = 1;
		while (player->getHealth() > 0 && enemy->getHealth() > 0) {
			cout << "Round " << roundCount << endl;
			cout << "==============================" << endl;

			player->setHealth(player->getHealth() - enemy->getDamage());
			cout << "Player: " << player->getHealth() << "\n";

			enemy->setHealth(enemy->getHealth() - player->getDamage());
			cout << "Enemy: " << enemy->getHealth() << "\n";

			roundCount++;
		}

		if (player->getHealth() > 0) {
			cout << "You win!";
			player->setXp(player->getXp() + enemy->getXpPlus());
		}
		else {
			cout << "You lose!";
		}
	}

	auto increaseCharacter(int randChoose) {
		if (randChoose == 1) {
			cout << "Level up! Congrats!";
		}
		else if (randChoose == 2) {
			player->setMaxHealth(player->getMaxHealth() + 150);
			cout << "Your health bar has increased! Congrats!";
		}
		else if (randChoose == 3) {
			player->setEnergy(player->getEnergy() + 150);
			cout << "Your energy bar has increased! Congrats!";
		}
		else if (randChoose == 4) {
			player->setAgility(player->getAgility() + 150);
			cout << "You become agiliter! Congrats!";
		}
		else if (randChoose == 5) {
			player->setEndurance(player->getEndurance() + 150);
			cout << "You become endurancer! Congrats!";
		}
		else if (randChoose == 6) {
			player->setPower(player->getPower() + 150);
			cout << "Power You have more power! Congrats!";
		}
		else if (randChoose == 7) {
			player->setXp(player->getXp() + 150);
			cout << "XP You become smarter! Congrats!";
		}
		else if (randChoose == 8) {
			int coin = betterRandomizer(1, 10);
			cout << "You got " << coin << "$ ! Congrats!";

			player->setWallet(player->getWallet() + coin);
		}
	}



	~Event() { }
};


int main() {
	srand(0);
	Engine* obj = new Engine();
	SaveLoad* saveload = NULL;
	Gamer* gamer = NULL;

	int loadChoose = obj->typeNameInt("Continue?(0-Continue, 1-New Game) Note: Type Q to end game");
	if (loadChoose != 1 && loadChoose != 0) {
		cerr << "\aError: Wrong value! Try again!";
		return 0;
	}
	else if (loadChoose == 0) {
		gamer = saveload->loadPlayer();
	}
	else {
		gamer = obj->createGamer(obj->typeName("Enter your name: "), obj->typeName("Enter your new character(barbar(+100 health, +50 power), tank(+200 health, +50 endurance), murder(+0 health, +50 agility) ): "));
	}
	Event* event = new Event(gamer);

	gamer->setWeapon(obj->createWeapon(obj->typeNameInt("Enter your new weapon(1 - flint and stone, 2 - sword, 3 - bow, 4 - fireball, 5 - axe, 6 - AK-47, 7 - HIPL): ")));
	gamer->setShield(obj->createShield(obj->typeNameInt("Enter your new shield(1 - package ATB, 2 - wood, 3 - stone, 4 - steel, 5 - IRIS, 6 - diamond, 7- magic shield): ")));
	while (true) {
		int chance = betterRandomizer(1, 100);

		if (chance <= 5) {
			event->mainPage(event->typeNameInt("Choose the option(1 - buy weapon, 2 - buy shield, 3 - buy potion, 4 - continue game"));
			cout << endl;
			system("pause");
		}
		else if (chance > 5 && chance <= 30) {
			event->increaseCharacter(betterRandomizer(1, 8));
			cout << endl;
			system("pause");
		}
		else if (chance > 30 && chance <= 70) {
			event->meetMonster();
			cout << endl;
			system("pause");
		}
		else if (chance > 70 && chance <= 72) {
			gamer->usePotion();
		}
		else {
			return NULL;
		}
		gamer->useSkill(1);

	}

	if (gamer->getXp() == 1000) {
		gamer->useSkill(3);
		cout << "\aLevel UP!!!\n";
	}

	if (betterRandomizer(0, 100) == 0) {
		gamer->useSkill(2);
	}

	if (_getch() == 'q') {
		saveload->savePlayer();
	}

}



