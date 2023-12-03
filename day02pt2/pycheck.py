file_path = "inputs.txt"

def fn(gd):
    checks = gd.split(';')
    mc3 = {'red': 0, 'green': 0, 'blue': 0}

    for check in checks:
        c3 = {'red': 0, 'green': 0, 'blue': 0}
        for dat in check.split(','):
            dat = dat.strip()
            if dat:
                c, col = dat.split()
                c3[col] += int(c)

        for col in mc3:
            mc3[col] = max(mc3[col], c3[col])

    return mc3

def parse_input():
    sum = 0
    with open(file_path, 'r') as file:
        for line in file:
            _, gd = line.split(':')
            mc3 = fn(gd)
            sum += mc3['red'] * mc3['green'] * mc3['blue']
            print(mc3['red'] * mc3['green'] * mc3['blue'])

    return sum

print(parse_input())