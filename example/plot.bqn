# Note that you must have CXBQN_PLOT enabled at configure time for this to work

plt←•cxbqn.plot

•Out "Available plotting utilities:"
•Show plt

# 10 values from the y axis in either direction
x←10-˜↕21

parab←2⋆˜x

"Parabola" plt.NamedPlot x‿parab

"Another Parabola" plt.NamedPlot x‿(2×parab)

plt.Title "Two Parabolas"

plt.Legend@
plt.Show@
