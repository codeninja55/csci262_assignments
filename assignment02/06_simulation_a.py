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

n_C = 0  # number of computers
n_X = 0  # number of X infected computers
n_W = 0  # number of W infected computers

# Get the number of computers
n_C = 10

computers = {x: State.UN_INF for x in range(1, n_C + 1)}

random.seed(2)
uninfected_sample = random.sample(list(computers.keys()), n_C)  # set up a random sample with no duplicates

choice = random.choice(uninfected_sample)  # select one to be infected at the beginning
computers[uninfected_sample.pop()] = State.X_INF

# Set pandas display options to fit width
pd.set_option('display.max_rows', 100)
pd.set_option('display.max_columns', 100)
pd.set_option('display.width', 1000)

for i in np.arange(0, 24.5, 0.5):
    time = i
    n_X = 0

    if i is 6.5:  # a counter worm, W has been developed and is deployed on one infected computer
        pass

    # every hour the worm X spreads from each infected computer to one previously uninfected computer.
    if i % 1 == 0:
        infected = [val for _, val in computers.items() if val == State.X_INF]
        n_X = len(infected)

        if uninfected_sample is None:
            continue
        elif n_X < len(uninfected_sample):
            for j in range(n_X):
                computers[uninfected_sample.pop()] = State.X_INF
        else:
            for k in range(len(uninfected_sample)):
                computers[uninfected_sample.pop()] = State.X_INF

        random.shuffle(uninfected_sample)

        computers_df = {'COMPUTER': [x for x in computers.keys()],
                        'STATE': [("X" if y == State.X_INF else "W" if y == State.W_INF else "U")
                                  for y in computers.values()]}
        df = pd.DataFrame.from_dict(computers_df, orient='index')
        # df = pd.DataFrame(computers, index=['STATE', ])
        # df[].replace(State.X_INF, 'X')
        # df['STATE'].replace(State.UN_INF, 'U')
        # df['STATE'].replace(State.W_INF, 'W')
        print("Time: " + str(time) + " ==> [ X Infected:  " + str(n_X) + " ] \n")
        print(df.to_string(header=False))
        # print(df)
        print("\n")
