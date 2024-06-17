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

        for y in range(0, nxC):
            for x in range(0, nyC):

                if not pauseExec:
                    # amount of alive neighbours
                    n_neigh = calculate_neighbours(gameState, x, y, params["automata_params"]["rules"], params["style_params"]["grid_x"], params["style_params"]["grid_y"], params["style_params"]["wrapping"])

                    # alive rule: must be alive and have x alive neighbours to stay alive
                    if (n_neigh == params["automata_params"]["alive"] and gameState[x, y] == 1):
                        newGameState[x, y] = 1

                    # dead rule: must be alive and have x alive neighbours to die
                    elif (n_neigh == params["automata_params"]["dead"] and gameState[x, y] == 1):
                        newGameState[x, y] = 0

                    # born rule: must be dead and have x alive neighbours to be born
                    elif (n_neigh == params["automata_params"]["born"] and gameState[x, y] == 0):
                        newGameState[x, y] = 1

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
