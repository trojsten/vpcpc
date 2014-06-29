import sys

if len(sys.argv) != 3:
  print ("Usage: %s input_file output_file" % sys.argv[0])
  sys.exit(254)

MAX_LINES = 10000
MAX_VALUE = 10000
FORMAT_ERROR = -1
POINTS_NOT_SEPARATED = -2

def cross(x1, y1, x2, y2):
  return x1 * y2 - x2 * y1

def which_side(point, line):
  return cross(line[2] - line[0], line[3] - line[1],
               point[0] - line[0], point[1] - line[1]) <= 0

def get_stamp(point, lines):
  return tuple([which_side(point, line) for line in lines])

def are_points_separated(points, lines):
  stamps = set(get_stamp(point, lines) for point in points)
  return len(stamps) == len(points)

def judge():

  with open(sys.argv[1], "r") as input_file:
    N = int(input_file.readline())
    points = [map(int, input_file.readline().split()) for i in range(N)]

  with open(sys.argv[2], "r") as output_file:
    try:
      L = int(output_file.readline())
    except EOFError:
      return FORMAT_ERROR  # there are not enough lines in the file
    except ValueError:
      return FORMAT_ERROR  # there is not an integer

    if L > MAX_LINES: return FORMAT_ERROR  # too many lines

    lines = []
    for i in range(L):
      try:
        line = output_file.readline()
      except EOFError:
        return FORMAT_ERROR  # there are not enough lines in the file

      line = line.split()
      if len(line) != 4: return FORMAT_ERROR # there must be exactly 4 integer on the line

      try:
        line = map(int, line)
      except ValueError:
        return FORMAT_ERROR

      for coordinate in line:
        if abs(coordinate) > MAX_VALUE:
          return FORMAT_ERROR

      if (line[0], line[1]) == (line[2], line[3]): return FORMAT_ERROR

      if not (line[0] == line[2] or
              line[1] == line[3] or
              line[0] - line[2] == line[1] - line[3] or
              line[0] - line[2] == line[3] - line[1]): return FORMAT_ERROR

      lines.append(line)

  if not are_points_separated(points, lines): return POINTS_NOT_SEPARATED

  return L

score = judge()
if score == FORMAT_ERROR:
  print("Output format is not followed.")
  sys.exit(1)
if score == POINTS_NOT_SEPARATED:
  print("Points were not separated by the lines.")
  sys.exit(2)
print(score)
