graph = {
	1 : [24, 2],
	2 : [1, 3],
	3 : [2, 4, 35, 36],
	4 : [3, 5],
	5 : [4, 6],
	6 : [5, 7],
	7 : [6, 8, 27, 28],
	8 : [7, 9],
	9 : [8, 10],
	10 : [9, 11],
	11 : [10, 12, 39, 40],
	12 : [11, 13],
	13 : [12, 14],
	14 : [13, 15],
	15 : [14, 16, 30, 31],
	16 : [15, 17],
	17 : [16, 18],
	18 : [17, 19],
	19 : [18, 20, 43, 44],
	20 : [19, 21],
	21 : [20, 22],
	22 : [21, 23],
	23 : [22, 24, 25, 33],
	24 : [23, 1],
	25 : [23, 34],
	26 : [34, 47],
	27 : [7, 37],
	28 : [7, 38],
	29 : [38, 48],
	30 : [15, 41],
	31 : [15, 42],
	32 : [42, 46],
	33 : [23, 45],
	34 : [25, 26, 35, 45],
	35 : [3, 34, 36],
	36 : [3, 35, 37],
	37 : [27, 36, 47, 38],
	38 : [28, 29, 39, 37],
	39 : [11, 38, 40],
	40 : [11, 39, 41],
	41 : [40, 48, 42, 30],
	42 : [41, 43, 31, 32],
	43 : [19, 42, 44],
	44 : [19, 43, 45],
	45 : [33, 34, 44, 46],
	46 : [32, 45],
	47 : [26, 37],
	48 : [29, 41]
}

similar_nodes = {
	25 : (1, 35, 34, 25),
	26 : (35, 36, 37, 47, 26, 34),
	27 : (5, 27, 37, 36),
	28 : (9, 39, 38, 28),
	29 : (29, 38, 39, 40, 41, 48),
	30 : (13, 30, 41, 40),
	31 : (17, 43, 42, 31),
	32 : (32, 42, 43, 44, 45, 46),
	33 : (21, 33, 45, 44)
}

#straight = 0
#hard_left = 1
#soft_left = 2
#soft_right = 3
#hard_right = 4
directions = {
	1 : (0,300),
	2 : (10, 225),
	3 : (40, 150),
	4 : (87, 87),
	5 : (150, 40),
	6 : (225, 10),
	7 : (300, 0),
	8 : (375, 10),
	9 : (450, 40),
	10 : (513, 87),
	11 : (560, 150),
	12 : (590, 225),
	13 : (600, 300),
	14 : (590, 375),
	15 : (560, 450),
	16 : (513, 513),
	17 : (450, 560),
	18 : (375, 590),
	19 : (300, 600),
	20 : (225, 590),
	21 : (150, 560),
	22 : (87, 513),
	23 : (40, 450),
	24 : (10, 375),
	25 : (85, 375),
	26 : (210, 300),
	27 : (260, 70),
	28 : (340, 70),
	29 : (345, 225),
	30 : (525, 375),
	31 : (475, 450),
	32 : (345, 375),
	33 : (120, 450),
	34 : (120, 300),
	35 : (85, 225),
	36 : (120, 150),
	37 : (210, 150),
	38 : (385, 150),
	39 : (475, 150),
	40 : (525, 225),
	41 : (475, 300),
	42 : (385, 450),
	43 : (340, 530),
	44 : (260, 530),
	45 : (210, 450),
	46 : (225, 375),
	47 : (225, 224),
	48 : (385, 300)
}

def bfs(start, end_list, graph):
	storage = {start : (0, '-')}
	queue = [start]
	while queue:
		current_node = queue.pop(0)
		hop = storage[current_node][0]
		for neighbour in graph[current_node]:
			if neighbour not in storage:
				storage[neighbour] = (hop + 1, current_node)
				queue.append(neighbour)
	#print(end_list)
	#pprint.pprint(storage)
	min_hop = 1000
	end_point =  None
	for end in end_list:
		if min_hop > storage[end][0]:
			min_hop = storage[end][0]
			end_point = end
	path = []
	current = end_point
	while current != start:
		path.insert(0, current)
		current = storage[current][1]
	return path

def current_best(start, end, current_orientation):
	block = 'n'
	#print('******',current_orientation)
	if end in similar_nodes:
		end_list = list(similar_nodes[end])
	else:
		end_list = [end]

	temp = graph.copy()

	path_to_follow = bfs(start, end_list, temp)
	#print(path_to_follow)
	if path_to_follow:
		end_node = path_to_follow[-1]
	else:
		end_node = None

	import math

	current_node = start
	while path_to_follow:
		next_node = path_to_follow.pop(0)
		print('From', current_node, 'To', next_node)
		direction_to_move = (directions[current_node][0] - directions[next_node][0], directions[current_node][1] - directions[next_node][1])
		angle_direction =  math.degrees(math.atan((direction_to_move[1]) /(direction_to_move[0])))
		#print(direction_to_move)
		#print('angle direction', angle_direction)
		if -3 < angle_direction < 3:
			if direction_to_move[0] > 0:
				angle_direction = 180
		elif direction_to_move[1] < 0:
			if angle_direction > 0:
				angle_direction = (360 - angle_direction)
			elif angle_direction < 0:
				angle_direction = (180 + abs(angle_direction))
		
		else:
			if angle_direction > 0:
				angle_direction = (180 - angle_direction)
			elif angle_direction < 0:
				angle_direction = abs(angle_direction)

		

		angle_direction = (angle_direction - current_orientation)
		if angle_direction < 0:
			angle_direction = 360 + angle_direction
		if angle_direction >= 360:
			angle_direction %= 360 
		move = None

		if angle_direction < 20 or angle_direction > 340:
			move = 'Straight'
		elif 160 < angle_direction < 200:
			move = 'Reverse'
		elif angle_direction < 90:
			move = 'Soft Left'
		elif angle_direction < 180:
			move = 'Hard Left'
		elif angle_direction < 270:
			move = 'Hard Right'
		else:
			move = 'Soft Right'
		current_orientation += angle_direction
		if current_orientation < 0:
			current_orientation = 360 + current_orientation
		if current_orientation >= 360:
			current_orientation %= 360

		print('******************Actual Move:', move)

		#print("Angle to move", angle_direction,"Current direction", current_orientation)
		block = input('Blocked or not: Y/N')
		if block in ['y','Y']:
			temp = graph.copy()
			temp[current_node].remove(next_node)
			print('******************Actual Move: Reverse')
			path_to_follow = bfs(current_node, end_list, temp)
			current_orientation += 180
			if current_orientation < 0:
				current_orientation = 360 + current_orientation
			if current_orientation >= 360:
				current_orientation %= 360
			#print(path_to_follow)
			continue
		if block == 'e':
			return 

		current_node = next_node
	if end_node:
		return end_node, current_orientation
	return None, current_orientation



#start and end node
start = 1
string = [7, 29, 26, 18, 24, 13, 30, 16, 20]
current_orientation = 0
for end in string:
	print(start, end)
	s, current_orientation = current_best(start, end, current_orientation)
	if s:
		start = s
	print('beep')