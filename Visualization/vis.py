import matplotlib.pyplot as plt

def visualize_secondary_structure(RNA_sequence, base_pairs):
    # Create a list to store the y-values of each base
    y_values = [0] * len(RNA_sequence)
    
    # Create a dictionary to store the x-values of each base
    x_values = {}
    
    # Assign x-values to each base
    current_x = 0
    for i, base in enumerate(RNA_sequence):
        x_values[i+1] = current_x
        current_x += 1
    
    # Plot bases
    plt.figure(figsize=(len(RNA_sequence)//2, 2))
    for i, base in enumerate(RNA_sequence):
        plt.text(x_values[i+1], y_values[i], base, ha='center', va='center', fontsize=12)
    
    # Plot base-pair connections
    for pair in base_pairs:
        i, j = pair
        plt.plot([x_values[i], x_values[j]], [0, 0], color='blue')
    
    plt.ylim(-1, 1)
    plt.axis('off')
    plt.title('RNA Secondary Structure')
    plt.show()

# Read RNA sequences and base-pair structures from file
with open('output.txt', 'r') as file:
    lines = file.readlines()
    for i in range(0, len(lines), 3):
        RNA_sequence = lines[i].strip().split(': ')[1]
        base_pairs = eval(lines[i+1].strip().split(': ')[1])  # Convert string representation of list to list
        visualize_secondary_structure(RNA_sequence, base_pairs)
