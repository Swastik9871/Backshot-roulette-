import time
import random

your_life = 4
dealer_life = 4

bullet = ["Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded", "Blank", "Loaded"]
load = random.choice(bullet)

power = ["Energy-Bar", "Silencer", "Thrill-Seeker", "See-Threw", "PeaceKeeper"] 

your_power = [random.choice(power) for _ in range(4)]
dealer_power = [random.choice(power) for _ in range(4)]

print("———THE-GAME-OF-LIFE———")

def EnergyBar(target_life):
    if target_life < 4:
        target_life += 1
        return target_life
    else:
        print('Your life is full')
        return target_life

def Silencer(target_life):
    target_life -= 2
    return target_life

def ThrillSeeker():
    global bullet
    bullet.remove("Loaded")
    print("Current bullet is removed.")

def SeeThrew():
    print('Current bullet is:', load)

def PeaceKeeper(target):
    return 'Skip'

def use_power(power, target_life, powers_list):
    if power == "Energy-Bar":
        target_life = EnergyBar(target_life)
    elif power == "Silencer":
        target_life = Silencer(target_life)
    elif power == "Thrill-Seeker":
        ThrillSeeker()
    elif power == "See-Threw":
        SeeThrew()
    elif power == "PeaceKeeper":
        return 'Skip'

    return target_life

def shoot(target, target_life, powers):
    global bullet

    if bullet:
        load = bullet.pop(0)
    else:
        load = None

    print('Bullet is:', load)
    time.sleep(1)

    if load == 'Loaded':
        if target == 'You':
            target_life -= 1
            print(f'{target} is hit! {target}\'s remaining life:', target_life)
        else:  # Dealer shooting
            if 'Silencer' in powers:
                target_life -= 2
            else:
                target_life -= 1
            print(f'{target} is hit! {target}\'s remaining life:', target_life)
    else:
        print('You are safe.')

    time.sleep(1)

    if powers:
        for power in powers:
            target_life = use_power(power, target_life, your_power if target == "You" else dealer_power)
    
    return target_life

def game():
    global your_life, dealer_life

    for i in range(len(bullet)):
        while dealer_life > 0 and your_life > 0:
            print('\nYour life:', 'ϟ' * dealer_life)
            print('Your Powers are', your_power)
            print('\nDealer\'s life:', 'ϟ' * your_life)
            print('Dealer Powers are', dealer_power)

            # Use power before target input
            your_powers = int(input('\n\nWrite 0 for first Power, 1 for second and so on. \nWhat power do you choose: '))
            if your_power:
                your_life = use_power(your_power[your_powers], your_life, your_power)

            target = input("\nChoose whom to shoot (You or Dealer): ").capitalize()
            dealer_powers = random.choice(dealer_power)

            if target == 'You':
                your_life = shoot('You', your_life, your_power)
            elif target == 'Dealer':
                dealer_life = shoot('Dealer', dealer_life, dealer_powers)
            elif target == 'Skip':
                print('Skipping turn...')
            else:
                print('Invalid choice. Please choose "You" or "Dealer".')

            if your_life <= 0:
                print('\nGame over! Dealer wins!\n\nYou Died\n')
            elif dealer_life <= 0:
                print('\nCongratulations! You win!')
            else:
                print('\nDealer\'s turn...')
                time.sleep(1)
                dealer_life = shoot('Dealer', dealer_life, dealer_powers)

game()