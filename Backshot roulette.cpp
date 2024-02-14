#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int your_life = 4;
int dealer_life = 4;
std::vector<std::string> bullet = {"Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded"};
std::string load;
std::vector<std::string> power = {"Energy-Bar", "Silencer", "Thrill-Seeker", "See-Threw", "PeaceKeeper"};
std::vector<std::string> your_power(4);
std::vector<std::string> dealer_power(4);

void EnergyBar(int& target_life) {
    if (target_life < 4) {
        target_life += 1;
    }
}

void Silencer(int& target_life) {
    target_life -= 2;
}

void ThrillSeeker() {
    auto it = std::find(bullet.begin(), bullet.end(), "Loaded");
    if (it != bullet.end()) {
        bullet.erase(it);
        std::cout << "Current bullet is removed." << std::endl;
    }
}

void SeeThrew() {
    std::cout << "Current bullet is: " << load << std::endl;
}

std::string PeaceKeeper(int target) {
    return "Skip";
}

int use_power(std::string power, int target_life, std::vector<std::string>& powers_list) {
    if (power == "Energy-Bar") {
        EnergyBar(target_life);
    } else if (power == "Silencer") {
        Silencer(target_life);
    } else if (power == "Thrill-Seeker") {
        ThrillSeeker();
    } else if (power == "See-Threw") {
        SeeThrew();
    } else if (power == "PeaceKeeper") {
        return 0; // Skip
    }
    return target_life;
}

int shoot(std::string target, int target_life, std::vector<std::string>& powers) {
    if (!bullet.empty()) {
        load = bullet.front();
        bullet.erase(bullet.begin());
    } else {
        load = "";
    }

    std::cout << "Bullet is: " << load << std::endl;
    sleep(1);

    if (load == "Loaded") {
        target_life -= 1;
        std::cout << target << " is hit! " << target << "'s remaining life: " << target_life << std::endl;
    } else {
        std::cout << "You are safe." << std::endl;
    }
    sleep(1);

    if (!powers.empty()) {
        for (const auto& power : powers) {
            target_life = use_power(power, target_life, powers);
        }
    }
    return target_life;
}

void game() {
    for (int i = 0; i < bullet.size(); ++i) {
        while (your_life > 0 && dealer_life > 0) {
            std::cout << "\nYour life: ";
            for (int j = 0; j < your_life; ++j) {
                std::cout << "ϟ";
            }
            std::cout << "\nYour Powers are: ";
            for (const auto& power : your_power) {
                std::cout << power << " ";
            }
            std::cout << "\nDealer's life: ";
            for (int j = 0; j < dealer_life; ++j) {
                std::cout << "ϟ";
            }
            std::cout << "\nDealer Powers are: ";
            for (const auto& power : dealer_power) {
                std::cout << power << " ";
            }
            std::cout << "\n\nWrite 0 for first Power, 1 for second and so on.\nWhat power do you choose: ";
            int your_powers;
            std::cin >> your_powers;
            if (!your_power.empty()) {
                your_life = use_power(your_power[your_powers], your_life, your_power);
            }
            std::string target;
            std::cout << "\nChoose whom to shoot (You or Dealer): ";
            std::cin >> target;
            std::vector<std::string> dealer_powers = {dealer_power[rand() % dealer_power.size()]};
            if (target == "You") {
                your_life = shoot("You", your_life, your_power);
            } else if (target == "Dealer") {
                dealer_life = shoot("Dealer", dealer_life, dealer_powers);
            } else if (target == "Skip") {
                std::cout << "Skipping turn..." << std::endl;
            } else {
                std::cout << "Invalid choice. Please choose \"You\" or \"Dealer\"." << std::endl;
            }
            if (your_life <= 0) {
                std::cout << "\nGame over! Dealer wins!\n\nYou Died\n" << std::endl;
            } else if (dealer_life <= 0) {
                std::cout << "\nCongratulations! You win!" << std::endl;
            } else {
                std::cout << "\nDealer's turn..." << std::endl;
                sleep(1);
                dealer_life = shoot("Dealer", dealer_life, dealer_powers);
            }
        }
    }
}

int main() {
    srand(time(0));
    your_power = {"Energy-Bar", "Silencer", "Thrill-Seeker", "See-Threw"};
    dealer_power = {"Energy-Bar", "Silencer", "Thrill-Seeker", "See-Threw"};
    std::cout << "———THE-GAME-OF-LIFE———" << std::endl;
    game();
    return 0;
}