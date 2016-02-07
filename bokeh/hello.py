from bokeh.plotting import figure, show, output_server

p = figure(title="Server Plot")
p.circle([1, 2, 3], [4, 5, 6])

output_server("hover")

show(p)