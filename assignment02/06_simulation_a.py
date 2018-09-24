import random
import numpy as np
import pandas as pd
from enum import Enum
from IPython.display import display, HTML


class State(Enum):
    UN_INF = 0
    X_INF = 1
    W_INF = 2


time = 0
n_c = 10  # number of computers
n_x = 0  # number of X infected computers

computers = {x: State.UN_INF for x in range(1, n_c + 1)}

random.seed(2)
uninfected_sample = random.sample(list(computers.keys()), n_c)  # set up a random sample with no duplicates

choice = random.choice(uninfected_sample)  # select one to be infected at the beginning
computers[uninfected_sample.pop()] = State.X_INF

# Set pandas display options to fit width
pd.set_option('display.max_rows', 100)
pd.set_option('display.max_columns', 100)
pd.set_option('display.width', 1000)

for i in np.arange(0, 24.5, 0.5):
    time = i

    # every hour the worm X spreads from each infected computer to one previously uninfected computer.
    if i % 1 == 0:
        infected = [val for _, val in computers.items() if val == State.X_INF]
        n_x = len(infected)

        if uninfected_sample is None:
            continue
        elif n_x < len(uninfected_sample):
            for j in range(n_x):
                computers[uninfected_sample.pop()] = State.X_INF
        else:
            for k in range(len(uninfected_sample)):
                computers[uninfected_sample.pop()] = State.X_INF

        random.shuffle(uninfected_sample)

        computers_df = {'COMPUTER': [x for x in computers.keys()],
                        'STATE': [("X" if y == State.X_INF else "W" if y == State.W_INF else "U")
                                  for y in computers.values()]}
        df = pd.DataFrame.from_dict(computers_df, orient='index')
        print("Time: " + str(time) + " ==> [ X Infected:  " + str(n_x) + " ] \n")
        print(df.to_string(header=False))
        print("\n")
