import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from IPython.display import display

n_x = 0  # number of x infected computers at t = 0
n_w = 0  # number of w infected computers
idx = 0

# initialise variable
table = {'t': [t for t in np.arange(0, 24.5, 0.5)],
         'x': [0 for _ in np.arange(0, 24.5, 0.5)],
         'w': [0 for _ in np.arange(0, 24.5, 0.5)]}


for i in table['t']:
    idx = int(i * 2)

    if i == np.float(0):
        n_x = 1
        table['x'][0] = n_x
    elif i == np.float(0.5):
        table['x'][1] = n_x

    if i >= np.float(1.0):

        if i % 1 == 0:  # on every hour
            n_x *= 2
            table['w'][idx] = n_w if i > np.float(6.5) else 0  # maintain w at hour mark
            table['x'][idx] = n_x

        elif i % 1 == 0.5:  # on every half hour
            if i == np.float(6.5):  # at t = 6.5, introduce w
                n_w = 1
                table['w'][idx] = n_w
                n_x = n_x - n_w
                table['x'][idx] = n_x

            if i > np.float(6.5):  # after introduction of w
                n_w *= 3

                if n_w > n_x:
                    n_w = (n_w / 3) + n_x

                n_x = int(n_x - (n_w - (n_w / 3))) if n_w < n_x and n_x > 0 else 0
                table['w'][idx] = n_w
            table['x'][idx] = n_x

df = pd.DataFrame(table)
display(df)
df.to_csv('out.csv')

# plot graph
# plt.plot(x='t', y='x', data=df, color='red', label='x infected')
# plt.plot(x='t', y='w', data=df, color='green', label='w infected')
# plt.legend()
# plt.show()


