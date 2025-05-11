# A simple restaurent billing software made using C language

---

# 🧾 Restaurant Billing System (C Project)

This is a simple and interactive **Restaurant Billing System** built using the C programming language. The system allows you to:

- Create and save customer bills
- Print bills to `.txt` files
- View all saved bills
- Search and print bills by customer name

---

## 📁 Features

- ✅ Create detailed customer bills with multiple items
- ✅ Save bills to a binary file (`bills.txt`)
- ✅ Prevent duplicate bill printing
- ✅ Generate customer-specific text files (e.g., `John_Doe.txt`)
- ✅ Search and print past bills by customer name
- ✅ Persistent data storage across sessions

---

## 🛠️ How to Compile

Make sure you have a C compiler installed (like `gcc`).

```bash
gcc billing_system.c -o billing_system
````

---

## ▶️ How to Run

```bash
./billing_system
```

---

## 📌 Usage Options

```
--- RESTAURANT BILLING SYSTEM ---
1. Create New Bill
2. View All Bills
3. Search Bill by Customer Name
4. Print Bill by Customer Name
5. Exit
```

---

## 📂 File Structure

* `billing_system.c` — The main source file.
* `bills.txt` — Stores all bill records in binary format.
* `<CustomerName>.txt` — Text file copy of the bill, only generated if requested.

---

## 💡 Example Flow

1. User selects **Create New Bill**
2. Enters customer name, number of items, item details
3. Gets a printed bill summary
4. Bill is saved to `bills.txt`
5. Option to print as a `.txt` file

---

## 🔐 Notes

* The `.txt` bill will not be re-generated if it already exists for the customer.
* All input supports spaces (e.g., item names like `Cheese Pizza` or customer name `John Doe`).

---

## 📄 License

This project is open-source and free to use for educational or personal purposes.

---

## 🤝 Contributing

Pull requests and improvements are welcome. Feel free to fork the repo and submit suggestions!
