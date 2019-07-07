from sys import argv

'''
Script to make a best case input and worst case input that has the same char count as a provided file.
'''

def main():
	if len(argv) != 2:
		print("Usage:")
		print(">> python make_best_and_worst_inputs.py <input_filename>")
		print("where the generated files will have the same char count as <input_filename>")
		return
	
	input_filename = argv[1]
	
	with open(input_filename, 'r') as f_in:
		with open("./books/clean/best.txt", 'w') as best:
			with open("./books/clean/worst.txt", 'w') as worst:
				for line in f_in:
					best_line = chr(32) * len(line)
					worst_line = chr(64) * len(line)
					best.write(best_line)
					worst.write(worst_line)
		
if __name__ == "__main__":
	main()