import numpy as np
import matplotlib.pyplot as plt

Nl = np.arange(9, 18, 1)            # sizes
idl = np.arange(1, 11, 1)           # job id
names = ["seq", "par1", "par2", "par4", "par8"]             # job name prefix
styles = ["bs", "ro", "g^", "ch", "y8"]               # plotstyle marker and color
datafile = "nqueens_data.txt"
with open(datafile, "w") as writefile:
    writefile.write("nQueens data for 10 runs: \n \n")
    for idx, name in enumerate(names):
        writefile.write("\n" + name + "\n \n")
        values = np.zeros((len(Nl), len(idl)))

        for j, N in enumerate(Nl):
            for i, ind in enumerate(idl):

                filename = "nq_" + name + "_N_" + str(N) + "_id_" + str(ind) + ".out"
                with open(filename, "r") as readfile:

                    lines = readfile.readlines()
                    values[j, i] = int(lines[1][18:len(lines[1]) - 5])

        values_statistical = np.zeros((len(Nl), 2))
        for n in xrange(len(Nl)):

            values_statistical[n, 0] = np.average(values[n, :])
            values_statistical[n, 1] = np.std(values[n, :])
            writefile.write("n = " + str(Nl[n]) + "  " + str(int(values_statistical[n, 0])) + " ms    " + "+/- " + str(round(100 * values_statistical[n, 1]/values_statistical[n, 0], 2)) + " % \n")

        plt.plot(Nl, values_statistical[:, 0], styles[idx], linestyle="dashed", label=name, markersize=3)

    plt.title("n Queens Timing", fontweight="bold", fontsize=13)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("time/ms", fontsize=12)
    plt.yscale("log")
    plt.legend()
    # plt.show()
    plt.savefig("timing.pdf", format="pdf", dpi=2400)

    plt.clf()
    for idx, name in enumerate(names):

        values = np.zeros((len(Nl), len(idl)))

        for j, N in enumerate(Nl):
            for i, ind in enumerate(idl):
                filename = "nq_" + name + "_N_" + str(N) + "_id_" + str(ind) + ".out"
                with open(filename, "r") as readfile:
                    lines = readfile.readlines()
                    values[j, i] = int(lines[1][18:len(lines[1]) - 5])

        values_statistical = np.zeros((len(Nl), 2))
        for n in xrange(len(Nl)):
            values_statistical[n, 0] = np.average(values[n, :])
            values_statistical[n, 1] = np.std(values[n, :])

        plt.plot(Nl, 100 * values_statistical[:, 1]/values_statistical[:, 0], styles[idx], linestyle="dashed", label=name)

    plt.title("n Queens Standard Deviation", fontweight="bold", fontsize=13)
    plt.xlabel("n", fontsize=12)
    plt.ylabel(r"$100 \times \frac{\Delta t}{t}$", fontsize=12)
    plt.legend()
    # plt.show()
    plt.savefig("errors.pdf", format="pdf", dpi=2400)