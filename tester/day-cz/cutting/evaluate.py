# Expects space separtaed lines in format "login score"
# Prints lines in the same format but scores are real

import math

results = []

while True:
  try: line = raw_input().split() # login score
  except EOFError: break
  results.append((int(line[1]), line[0]))

results.sort()
Lmin = results[0][0]

for result in results:
  L = result[0]
  score = 10 * (1 - math.sqrt(1 - 1.0 * Lmin/L))
  print result[1],score
