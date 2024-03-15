

series = {
    6: [1.0, 1.5, 2.2, 3.3, 4.7, 6.8],
         12: [1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2],
    }

def calc_voltage(voltage, rl, r):
    current = voltage / (rl + r)
    return (current * rl, current * r)

def calc_parallel(r, times):
    r_temp = 0
    for _ in range(times):
        r_temp += 1. / r
    return 1 / r_temp

def is_nice(a):
    if round(a) == 0:
        return False
    if abs(a - round(a)) < 0.000001:
        return True
    return False

voltages = [3.3, 5, 9, 10, 12, 20]

num_found = 0
for voltage in voltages:
    for rl_r in series:
        for r1_r in series:
            for rl_f in range(0,4):
                for r1_f in range(0,4):
                    for rl_v in series[rl_r]:
                        for r1_v in series[r1_r]:
                            rl_v = rl_v * 10 ** rl_f
                            r1_v = r1_v * 10 ** r1_f
                            res1 = calc_voltage(voltage, rl_v, calc_parallel(r1_v, 1))
                            res2 = calc_voltage(voltage, rl_v, calc_parallel(r1_v, 2))
                            res3 = calc_voltage(voltage, rl_v, calc_parallel(r1_v, 3))
                            if is_nice(res1[0]) and is_nice(res1[1]) and is_nice(res2[0]) and is_nice(res2[1]) and is_nice(res3[0]) and is_nice(res3[1]) and is_nice(rl_v) and is_nice(r1_v):
                                print("--------Found nice------")
                                print("Voltage:", voltage)
                                print("RS", rl_r, "RL:", rl_v)
                                print("RS", r1_r, "R1:", r1_v)
                                print("1 R1:", res1)
                                print("2 R1:", res2)
                                print("3 R1:", res3)
                                num_found += 1

print("Found nice values", num_found)
