from tkinter import *
import random

root = Tk()
root.geometry("330x600")
root.title("Tic Tac Toe")

root.resizable(0, 0)

frame1 = Frame(root)
frame1.pack()
titleLabel = Label(frame1, text="Tic Tac Toe", font=("Arial", 26), bg="orange", width=16)
titleLabel.grid(row=0, column=0)

optionFrame = Frame(root, bg="grey")
optionFrame.pack()

frame2 = Frame(root, bg="yellow")
frame2.pack()

board = {1: " ", 2: " ", 3: " ",
         4: " ", 5: " ", 6: " ",
         7: " ", 8: " ", 9: " "}

turn = "x"
game_end = False
mode = "singlePlayer"
difficulty = "hard"

def changeModeToSinglePlayer():
    global mode
    mode = "singlePlayer"
    singlePlayerButton["bg"] = "lightgreen"
    multiPlayerButton["bg"] = "lightgrey"
    easyButton["state"] = "normal"
    hardButton["state"] = "normal"

def changeModeToMultiplayer():
    global mode
    mode = "multiPlayer"
    multiPlayerButton["bg"] = "lightgreen"
    singlePlayerButton["bg"] = "lightgrey"
    easyButton["state"] = "disabled"
    hardButton["state"] = "disabled"

def setDifficultyEasy():
    global difficulty
    difficulty = "easy"
    easyButton["bg"] = "lightgreen"
    hardButton["bg"] = "lightgrey"

def setDifficultyHard():
    global difficulty
    difficulty = "hard"
    hardButton["bg"] = "lightgreen"
    easyButton["bg"] = "lightgrey"

def updateBoard():
    for key in board.keys():
        buttons[key-1]["text"] = board[key]

def checkForWin(player):
    if (board[1] == board[2] == board[3] == player or
        board[4] == board[5] == board[6] == player or
        board[7] == board[8] == board[9] == player or
        board[1] == board[4] == board[7] == player or
        board[2] == board[5] == board[8] == player or
        board[3] == board[6] == board[9] == player or
        board[1] == board[5] == board[9] == player or
        board[3] == board[5] == board[7] == player):
        return True
    return False

def checkForDraw():
    for i in board.keys():
        if board[i] == " ":
            return False
    return True

def restartGame():
    global game_end
    game_end = False
    for button in buttons:
        button["text"] = " "
    for i in board.keys():
        board[i] = " "
    titleLabel.config(text="Tic Tac Toe")

def minimax(board, isMaximizing):
    if checkForWin("o"):
        rand_num = random.choice([1, 2, 3, 4, 5, 6, 7, 8 ,9, 10])
        if difficulty == "easy":
            if rand_num < 6:
                return 1
            else:
                return -2
            
        elif difficulty == "hard":
            if rand_num < 10:
                return 1
            else:
                return -2
    if checkForWin("x"):
        return -1
    if checkForDraw():
        return 0
    if isMaximizing:
        bestScore = -100
        for key in board.keys():
            if board[key] == " ":
                board[key] = "o"
                score = minimax(board, False)
                board[key] = " "
                if score > bestScore:
                    bestScore = score
        return bestScore
    else:
        bestScore = 100
        for key in board.keys():
            if board[key] == " ":
                board[key] = "x"
                score = minimax(board, True)
                board[key] = " "
                if score < bestScore:
                    bestScore = score
        return bestScore

def playComputer():
    bestScore = -100
    bestMove = 0
    for key in board.keys():
        if board[key] == " ":
            board[key] = "o"
            score = minimax(board, False)
            board[key] = " "
            if score > bestScore:
                bestScore = score
                bestMove = key
    board[bestMove] = "o"

def play(event):
    global turn, game_end
    if game_end:
        return
    button = event.widget
    buttonText = str(button)
    clicked = buttonText[-1]
    if clicked == "n" :
        clicked = 1
    else :
        clicked = int(clicked)

    if button["text"] == " ":
        if turn == "x":
            board[clicked] = turn
            if checkForWin(turn):
                winningLabel = Label(frame1, text=f"{turn} wins the game", bg="orange", font=("Arial", 26), width=16)
                winningLabel.grid(row=0, column=0, columnspan=3)
                game_end = True
            turn = "o"
            updateBoard()
            if mode == "singlePlayer" and not game_end:
                playComputer()
                if checkForWin("o"):
                    winningLabel = Label(frame1, text=f"o wins the game", bg="orange", font=("Arial", 26), width=16)
                    winningLabel.grid(row=0, column=0, columnspan=3)
                    game_end = True
                turn = "x"
                updateBoard()
        else:
            board[clicked] = turn
            updateBoard()
            if checkForWin(turn):
                winningLabel = Label(frame1, text=f"{turn} wins the game", bg="orange", font=("Arial", 26), width=16)
                winningLabel.grid(row=0, column=0, columnspan=3)
                game_end = True
            turn = "x"
        if checkForDraw() and not game_end:
            drawLabel = Label(frame1, text="Game Draw", bg="orange", font=("Arial", 26), width=16)
            drawLabel.grid(row=0, column=0, columnspan=3)

# ------ UI --------

# Change Mode options
singlePlayerButton = Button(optionFrame, text="SinglePlayer", width=13, height=1, font=("Arial", 15), bg="lightgrey", relief=RAISED, borderwidth=5, command=changeModeToSinglePlayer)
singlePlayerButton.grid(row=0, column=0, columnspan=1, sticky=NW)

multiPlayerButton = Button(optionFrame, text="Multiplayer", width=13, height=1, font=("Arial", 15), bg="lightgrey", relief=RAISED, borderwidth=5, command=changeModeToMultiplayer)
multiPlayerButton.grid(row=0, column=1, columnspan=1, sticky=NW)

easyButton = Button(optionFrame, text="Easy", width=13, height=1, font=("Arial", 15), bg="lightgrey", relief=RAISED, borderwidth=5, command=setDifficultyEasy, state="normal")
easyButton.grid(row=1, column=0, columnspan=1, sticky=NW)

hardButton = Button(optionFrame, text="Hard", width=13, height=1, font=("Arial", 15), bg="lightgrey", relief=RAISED, borderwidth=5, command=setDifficultyHard, state="normal")
hardButton.grid(row=1, column=1, columnspan=1, sticky=NW)

# Tic Tac Toe Board
buttons = []
for i in range(9):
    button = Button(frame2, text=" ", width=4, height=2, font=("Arial", 30), bg="yellow", relief=RAISED, borderwidth=5)
    button.grid(row=i//3, column=i%3)
    button.bind("<Button-1>", play)
    buttons.append(button)

restartButton = Button(frame2, text="Restart Game", width=19, height=1, font=("Arial", 20), bg="Green", relief=RAISED, borderwidth=5, command=restartGame)
restartButton.grid(row=4, column=0, columnspan=3)

root.mainloop()
