# 🌍 Town Management System Using AVL Tree and Hash Table

This C project manages towns and their metadata using:
- An **AVL Tree** (for sorted data operations)
- A **Hash Table** (for fast lookup and deletion)

## 🚀 Features

- 🌲 Insert, update, delete towns in AVL tree.
- 📖 Read data from `district.txt` file.
- 🔍 Search towns by name, population, or municipality status.
- 🧠 Display towns in alphabetical order.
- 💾 Save tree to file (`towns.txt`) and populate hash table.
- 🧮 Compute hash table size and load factor.
- 📦 Export hash table data back to file.
- 🧼 Delete and search town records from hash table.

## 📁 File Structure

- `main.c` — Core logic for AVL tree and hash table operations, user interface, and menu.
- `avl_tree.h` / `avl_tree.c` — AVL Tree structure, balancing logic, insertion, deletion, and traversal.
- `hash_table.h` / `hash_table.c` — Hash Table implementation, including insert, search, delete, and load factor calculation.
- `district.txt` — Input file containing town data in the format `District:Town:Population:Elevation:yes/no`.
- `towns.txt` — Output file generated after saving AVL tree and hash table data.
- `README.md` — Project documentation and usage instructions.




## 📥 Input Format

Your `district.txt` should look like this:

DistrictA:TownX:12000:350:yes 


DistrictB:TownY:8000:210:no 



DistrictC:TownZ:23000:400:yes



---
## ✍️ Author:
Name: Yara Khattab

📧 Email: yarakhattab16@gmail.com



🔗 GitHub: github.com/yarakhattab

