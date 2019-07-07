from sys import argv

'''
Script to duplicate a file's contents n times.
'''

def main():
	if len(argv) != 4:
		print("Usage:")
		print(">> python duplicate.py <input_filename> <output_filename> <number of times to duplicate contents>")
		return
	
	input_filename = argv[1]
	duplicate_count = int(argv[3])
	out_filename = argv[2]
	
	if ('duplicate' not in out_filename):
		print("output filename must include the substring 'duplicate'")
		return
	
	with open(out_filename, 'w') as f_out:
		for i in range(duplicate_count):
			with open(input_filename, 'r') as f_in:
				for line in f_in:
					f_out.write(line)
		
if __name__ == "__main__":
	main()