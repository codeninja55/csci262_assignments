import random
import numpy as np
import pandas as pd
from enum import Enum


class State(Enum):
    UN_INF = 0
    X_INF = 1
    W_INF = 2


# Initialise counters
time = 0
n_x = 0  # number of X infected computers
n_w = 0  # number of W infected computers
n_comps = 10  # number of computers

computers = {x: State.UN_INF for x in range(1, n_comps + 1)}

x_infected_sample = []
w_infected_sample = []

random.seed(2)
uninfected_sample = random.sample(list(computers.keys()), n_comps)  # set up a random sample with no duplicates

random.shuffle(uninfected_sample)  # shuffle the sample so popping off the end is different
computers[uninfected_sample.pop()] = State.X_INF  # select one to be infected at the beginning

# Set pandas display options to fit width
pd.set_option('display.max_rows', 100)
pd.set_option('display.max_columns', 100)
pd.set_option('display.width', 1000)

# main program loop - increment time every 0.5 hour
for i in np.arange(0, 24.5, 0.5):
    time = i

    # every hour the worm X spreads from each infected computer to one previously uninfected computer.
    if i % 1 == 0:
        x_infected_sample = [key for key, val in computers.items() if val == State.X_INF or val == State.W_INF]
        n_x = len(x_infected_sample)

        if uninfected_sample is None:
            continue
        elif n_x < len(uninfected_sample):
            for j in range(n_x):
                computers[uninfected_sample.pop()] = State.X_INF
        else:
            for k in range(len(uninfected_sample)):
                computers[uninfected_sample.pop()] = State.X_INF

        random.shuffle(uninfected_sample)
        random.shuffle(x_infected_sample)

    elif i > 7 and i % 1 == 0.5:  # W spreads on each offset half hour
        # The counter worm W spreads more quickly than X, with each W spreading to two X hosts each hour
        w_infected_sample = [key for key, val in computers.items() if val == State.W_INF]
        n_w = len(w_infected_sample)

        if w_infected_sample is None:
            continue
        elif n_w < n_comps:
            for l in range(n_w * 2):
                computers[x_infected_sample.pop()] = State.W_INF

    if i == 6.5:  # a counter worm, W has been developed and is deployed on one infected computer
        w_choice = random.choice(x_infected_sample)
        computers[w_choice] = State.W_INF
        n_w = 1

    computers_df = {'COMPUTER': [x for x in computers.keys()],
                    'STATE': [("X" if y == State.X_INF else "W" if y == State.W_INF else "U")
                              for y in computers.values()]}
    df = pd.DataFrame.from_dict(computers_df, orient='index')
    print("Time: " + str(time) + " ==> [ X Infected:  " + str(n_x) + " ] [ W Infected: " + str(n_w) + " ]")
    print(df.to_string(header=False) + "\n")
