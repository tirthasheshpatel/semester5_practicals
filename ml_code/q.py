import numpy as np

R = np.array([
  [-1, -1, -1, -1, 0, -1],
  [-1, -1, -1, 0, -1, 100],
  [-1, -1, -1, 0, -1, -1],
  [-1, 0, 0, -1, 0, -1],
  [0, -1, -1, 0, -1, 100],
  [-1, 0, -1, -1, 0, 100]
])

gamma = 0.8

Q = np.zeros_like(R)

state_action_pairs = {
  0: [4],
  1: [3, 5],
  2: [3],
  3: [1, 2, 4],
  4: [0, 3, 5],
  5: [1, 4, 5]
}

goal_state    = 5
episodes      = 10
t             = 1


for e in range(1, episodes+1):
  if e == 1  : current_state = 1
  elif e == 2: current_state = 3
  else       : current_state = np.random.choice([0,1,2,3,4,5])
  while current_state != goal_state:
    next_state = np.random.choice(state_action_pairs[current_state])
    rewards = [Q[next_state, next_next_state]
               for next_next_state in state_action_pairs[next_state]]

    maxr = np.max(rewards)

    Q[current_state, next_state] = (R[current_state, next_state] +
                                    gamma * maxr)

    current_state = next_state
    print(f"At time t={t}")
    print(f"{Q=}")
    t+=1
  print(f"Episode {e} finished")
