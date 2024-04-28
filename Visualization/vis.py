import tkinter as tk
import time
import matplotlib.pyplot as plt
import networkx as nx
from PIL import Image, ImageTk
import argparse

def draw_rna_structure(sequence, pairs):
    G = nx.Graph()
    
    # Add nodes
    for j, base in enumerate(sequence):
        G.add_node(j, label=base)
    
    # Add edges for base pairs
    for pair in pairs:
        G.add_edge(pair[0]-1, pair[1]-1)
    
    # Add edges between adjacent pairs
    for j in range(len(sequence) - 1):
        G.add_edge(j, j + 1)
    
    # Draw the RNA structure
    pos = nx.spring_layout(G)
    labels = nx.get_node_attributes(G, 'label')
    nx.draw(G, pos, with_labels=True, labels=labels, node_color='lightblue', font_size=8)
    plt.title(f"RNA Structure")
    image_path = "rna_structure.png"
    plt.savefig(image_path, dpi=300, bbox_inches='tight')
    plt.clf()

    return image_path

def RNApairing(RNA, i, j):
    pairings = {'A': 'U', 'U': 'A', 'G': 'C', 'C': 'G'}
    return RNA[i] == pairings.get(RNA[j])

def getSecondaryStruct(optChoice, i, j, RNA, basePairs, depth=0):
    if i >= j - 4:
        return

    t = optChoice[i][j] - 1
    basePairs.append((t + 1, j + 1))

    if RNApairing(RNA, t, j):
        # Update the Text widget with the current basePairs and color it blue
        time.sleep(0.5)
        text_output.insert(tk.END, '  ' * depth + f'Pair: {t + 1, j + 1}\n', 'blue')
        text_output.tag_config('blue', foreground='blue')
        root.update()  # Update the GUI

        getSecondaryStruct(optChoice, i, t - 1, RNA, basePairs, depth + 1)
        getSecondaryStruct(optChoice, t + 1, j - 1, RNA, basePairs, depth + 1)
    else:
        # Update the Text widget with the current basePairs without coloring
        time.sleep(0.5)
        text_output.insert(tk.END, '  ' * depth + f'Pair: {t + 1, j + 1}\n')
        root.update()  # Update the GUI

        getSecondaryStruct(optChoice, i, j - 1, RNA, basePairs, depth + 1)
        
def RNAfolding(RNA, frame_optChoice, frame_optValue):
    n = len(RNA)
    optValue = [[0] * n for _ in range(n)]
    optChoice = [[0] * n for _ in range(n)]
    basePairs = []

    for k in range(5, n):
        for i in range(n - k):
            j = i + k
            maximum = float('-inf')
            choice = -1
            first = optValue[i][j - 1] if j > 0 else 0
            for t in range(i, j - 4):
                if RNApairing(RNA, t, j):
                    if 1 + (optValue[i][t - 1] if t > 0 else 0) + (optValue[t + 1][j - 1] if j > 0 else 0) > maximum:
                        maximum = 1 + (optValue[i][t - 1] if t > 0 else 0) + (optValue[t + 1][j - 1] if j > 0 else 0)
                        choice = t
            if maximum > first:
                optValue[i][j] = maximum
                optChoice[i][j] = choice + 1
            else:
                optValue[i][j] = first

            time.sleep(0.2)
            # Call a function to update the GUI with the current optChoice and optValue tables
            update_table(optChoice, optValue, frame_optChoice, frame_optValue)
            root.update()  # Update the GUI
            
    basePairs.clear()
    getSecondaryStruct(optChoice, 0, n - 1, RNA, basePairs)

    image_path = draw_rna_structure(RNA, basePairs)

    return optValue, optChoice, image_path

# Initialize the labels once and store them in 2D lists
labels_optChoice = []
labels_optValue = []

def update_table(optChoice, optValue, frame_optChoice, frame_optValue):
    global labels_optChoice, labels_optValue

    # If the labels haven't been created yet, create them
    if not labels_optChoice:
        for i in range(len(optChoice)):
            labels_optChoice.append([])
            for j in range(len(optChoice[i])):
                label = tk.Label(frame_optChoice, text=str(optChoice[i][j]), borderwidth=1, relief="solid", width=3)
                label.grid(row=i, column=j)
                labels_optChoice[-1].append(label)

    # If the labels haven't been created yet, create them
    if not labels_optValue:
        for i in range(len(optValue)):
            labels_optValue.append([])
            for j in range(len(optValue[i])):
                label = tk.Label(frame_optValue, text=str(optValue[i][j]), borderwidth=1, relief="solid", width=3)
                label.grid(row=i, column=j)
                labels_optValue[-1].append(label)

    # Update the labels with the current optChoice and optValue tables
    for i in range(len(optChoice)):
        for j in range(len(optChoice[i])):
            if labels_optChoice[i][j]['text'] != str(optChoice[i][j]):
                labels_optChoice[i][j]['text'] = str(optChoice[i][j])
                labels_optChoice[i][j]['fg'] = 'red'
            else:
                labels_optChoice[i][j]['fg'] = 'black'

    for i in range(len(optValue)):
        for j in range(len(optValue[i])):
            if labels_optValue[i][j]['text'] != str(optValue[i][j]):
                labels_optValue[i][j]['text'] = str(optValue[i][j])
                labels_optValue[i][j]['fg'] = 'red'
            else:
                labels_optValue[i][j]['fg'] = 'black'

def print_table(table):
    for row in table:
        print(row)
        
def close():
    root.quit()  # Stop the Tkinter main loop
    root.destroy()  # Destroy the Tkinter window

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description='RNA Folding Visualization')
    parser.add_argument('RNA', type=str, help='The RNA sequence')
    args = parser.parse_args()

    # Create a Tkinter GUI window
    global root
    root = tk.Tk()
    root.title("RNA Folding Visualization")

    # Create a main frame
    main_frame = tk.Frame(root)
    main_frame.pack(fill=tk.BOTH, expand=1)

    # Create a canvas
    my_canvas = tk.Canvas(main_frame)
    my_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=1)

    # Create another frame inside the canvas
    second_frame = tk.Frame(my_canvas)

    # Add that new frame to a window in the canvas
    my_canvas.create_window((0, 0), window=second_frame, anchor="nw")

    # Add an entry for RNA input string
    entry_RNA = tk.Entry(second_frame, width=60)
    entry_RNA.insert(0, args.RNA)
    entry_RNA.grid(row=0, column=0, columnspan=2, padx=10, pady=10)

    # Add frames for tables
    global frame_optChoice, frame_optValue
    frame_optChoice = tk.Frame(second_frame, bd=2, relief="ridge")
    frame_optChoice.grid(row=1, column=0, padx=10, pady=10)

    frame_optValue = tk.Frame(second_frame, bd=2, relief="ridge")
    frame_optValue.grid(row=1, column=1, padx=10, pady=10)

    # Add a Text widget for displaying base pairs
    global text_output
    text_output = tk.Text(second_frame, width=50, height=10)
    text_output.grid(row=2, column=0, columnspan=2, padx=10, pady=10)

    optValue, optChoice, image_path = RNAfolding(args.RNA, frame_optChoice, frame_optValue)

    # Delete the frames and Text widget
    frame_optChoice.grid_forget()
    frame_optValue.grid_forget()
    text_output.grid_forget()

    # Add an empty Label widget that spans the entire grid
    empty_label = tk.Label(second_frame)
    empty_label.grid(row=0, column=0, rowspan=3, columnspan=2, sticky='nsew')

    # Display the image
    img = Image.open(image_path)
    img = img.resize((600, 600), Image.LANCZOS)  # Resize the image
    img = ImageTk.PhotoImage(img)
    frame_img = tk.Frame(second_frame)  # Create a new frame for the image
    frame_img.grid(row=1, column=0, columnspan=2)
    img_label = tk.Label(frame_img, image=img)
    img_label.image = img  # keep a reference to the image
    img_label.pack()

    # Close the window after 5 seconds
    root.after(5000, close)

    root.mainloop()

if __name__ == "__main__":
    main()