# The sum of directories with size < 100000.
$answer1 = 0
# The minimum size of an existing directory to delete in order to push the used memory below 70000000.
$answer2 = 2493364224933642

# Directory hash. Files are prefixed with . e.g. .file1 .file2 .
dirs = {'' => {}}
# Current path.
path = ""

# Looks at the current directory's nested hash, checks if a key is present,
# and sets it to a given value if it is not.
def optCreate(currDir, key, value)
  if !currDir || !currDir.has_key?(key) then
    currDir[key] = value
  end
end

# Read the commands and figure out what the local storage looks like.
f = File.open("input.txt", "r")
f.each_line do |line|
  words = line.split(' ')
  path = "/" + path if path[0] != "/"
  pwd = path.split("/")
  
  if pwd.empty? then pwd = [""] end
  currDir = dirs.dig(*pwd)

  if words[0] == "$" then
    if words[1] == "cd" then
      if words[2] == ".." then # Going out one.
        path = path.split('/').slice(0..-2).join('/') + "/"
      elsif words[2] == "/" then # Back to home.
        path = "/"
      else # Going into a directory.
        optCreate(currDir, words[2], {})
        words[2] += "/"
        path += words[2]
      end
    end
  elsif words[0] == "dir" then # A directory has been spotted.
    optCreate(currDir, words[1], {})
  elsif words[0] == "ls" then # ls command, no info on this line.
    next
  else # A file line, containing the size and name.
    optCreate(currDir, "." + words[1], words[0].to_i)
  end
end
f.close

# Adds up the sums of each directory and sums the ones beneath
# the threshold to the first answer.
def func(hash)
  sum = 0
  hash.each do |k, v|
    if v.is_a? Integer
      sum += v
    else
      sum += func(v)
    end
  end
  if(sum <= 100000) then
    $answer1 += sum
  end
  sum
end

total = func(dirs)
$goal = 30000000 - (70000000 - total)

# Adds up the sums of each directory and finds the smallest one
# that can free up enough space to reach the goal.
def func2(hash)
  sum = 0
  hash.each do |k, v|
    if v.is_a? Integer
      sum += v
    else
      sum += func2(v)
    end
  end
  if(sum >= $goal)
    $answer2 = $answer2 < sum ? $answer2 : sum
  end
  sum
end

func2(dirs)

# Write the output
File.open('output.txt', 'w') { |file| 
  file.write($answer1 , " ", $answer2)
}