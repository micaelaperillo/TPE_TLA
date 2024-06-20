import pygame
import numpy as np
import time
import tk as tk
modified_params= {
	"automata_params" : {
		"alive":5,
		"dead":6,
		"born":3,
		"rules": {
			(-1, -2)
			,(-2, -3)
			,(-3, -2)
			,(-2, -1)
			,(-1, 0)
			,(0, -1)
		}
	},
	"style_params": {
		"grid_x":100,
		"grid_y":100,
		"window_height" : 768 , 
		"window_width" : 1280 , 
		"wrapping" : True , 
		"bg_color" : "#000000" , 
		"color" : [ "#12DCFF" , "#000FFD" , "#FFFFFF" ] , 
	}
}
default_params = { "style_params" : {
    "initial_cells" : [],
    "window_width" : 800,
    "window_height" : 600,
    "wrapping" : "True",
    "min_time_between_updates" : 1,
    "bg_color" : "#000000" ,
    "color" : [ "#FFFFFF" ] ,
    }
}

def deep_update(source, overrides):
    for key, value in overrides.items():
        if isinstance(value, dict) and key in source and isinstance(source[key], dict):
            deep_update(source[key], value)
        else:
            source[key] = value

params = default_params.copy()
deep_update(params, modified_params)


def help():
    popup = tk.Tk()
    popup.wm_title("Help")
    label = tk.Label(popup, text = '''
    Commands:
    - x: closes window
    - n: creates new game
    - space: pauses/reloads game
    - h: opens help''')
    label.pack(side="top", padx=20, pady=10)
    button = tk.Button(popup, text="OK", command=popup.destroy)
    button.pack()
    # to center the popup
    screen_width = popup.winfo_screenwidth()
    screen_height = popup.winfo_screenheight()
    # calculates the position
    x = (screen_width - popup.winfo_reqwidth()) / 2
    y = (screen_height - popup.winfo_reqheight()) / 2
    popup.geometry("+%d+%d" % (x, y))

    popup.mainloop()

def calculate_neighbours(state, x, y, rules, dim_x, dim_y, wrapping):
    rules = list(rules)
    neighbours = 0

    if (wrapping):
        for rule in rules:
            x_rule, y_rule = rule
            if state[(x + x_rule) % dim_x, (y + y_rule) % dim_y] == 1:
                neighbours += 1

    else:
        for rule in rules:
            x_rule, y_rule = rule
            if x + x_rule >= 0 and x + x_rule < dim_x and y + y_rule >= 0 and y + y_rule < dim_y:
                if state[x + x_rule, y + y_rule] == 1:
                    neighbours += 1

    return neighbours

def main():

    pygame.init()

    width, height = 1000, 1000
    screen = pygame.display.set_mode((height, width))

    bg = params["style_params"]["bg_color"]
    screen.fill(bg)
    nxC, nyC = params["style_params"]["grid_x"], params["style_params"]["grid_y"]

    dimCW = width / nxC
    dimCH = height / nyC

    # state: alive = 1, dead = 0
    gameState = np.zeros((nxC, nyC))

    # execution control
    pauseExec = True
    running = True

    generation = 0
    title = f"CAL 9000 - Generation number: {generation}"

    pygame.display.set_caption(title)

    while running:

        newGameState = np.copy(gameState)

        screen.fill(bg)
        time.sleep(0.1)

        ev = pygame.event.get()

        for event in ev:

            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_x:
                    running = False
                if event.key == pygame.K_SPACE:
                    pauseExec = not pauseExec
                if event.key == pygame.K_n:
                    newGameState = np.zeros((nxC, nyC))
                    pauseExec = True
                    generation = 0
                if event.key == pygame.K_h:
                    help()

            mouseClick = pygame.mouse.get_pressed()

            if sum(mouseClick) > 0:
                posX, posY = pygame.mouse.get_pos()
                celX, celY = int(np.floor(posX / dimCW)), int(np.floor(posY / dimCH))
                newGameState[celX, celY] = not gameState[celX, celY]

        for y in range(0, nyC):
            for x in range(0, nxC):

                if not pauseExec:
                    # amount of alive neighbours
                    n_neigh = calculate_neighbours(gameState, x, y, params["automata_params"]["rules"], params["style_params"]["grid_x"], params["style_params"]["grid_y"], params["style_params"]["wrapping"])

                    # born rule: must be dead and have x alive neighbours or more to be born
                    if (n_neigh >= params["automata_params"]["born"] and gameState[x, y] == 0):
                        newGameState[x, y] = 1

                    # dead rule: must be alive and have x alive neighbours or more to die
                    elif (n_neigh >= params["automata_params"]["dead"] and gameState[x, y] == 1):
                        newGameState[x, y] = 0

                    # alive rule: must be alive and have at least x alive neighbours to stay alive
                    elif (n_neigh >= params["automata_params"]["alive"] and gameState[x, y] == 1):
                        newGameState[x, y] = 1

                    # there's not enough neighbors to stay alive, so it dies
                    else:
                        newGameState[x, y] = 0;

                pol = [ ((x)   * dimCW, (y)   * dimCH),
                        ((x+1) * dimCW, (y)   * dimCH),
                        ((x+1) * dimCW, (y+1) * dimCH),
                        ((x)   * dimCW, (y+1) * dimCH)]

                if newGameState[x, y] == 0:
                    pygame.draw.polygon(screen, (128, 128, 128), pol, width=1)
                else:
                    color_index = generation % len(params["style_params"]["color"])
                    pygame.draw.polygon(screen, params["style_params"]["color"][color_index], pol, width=0)

        if pauseExec:
            title = "CAL 9000 - PAUSED"
        else:
            generation += 1
            title = f"CAL 9000 - Generation number: {generation}"

        pygame.display.set_caption(title)
        gameState = np.copy(newGameState)

        pygame.display.flip()
if __name__ == "__main__":
	main()
