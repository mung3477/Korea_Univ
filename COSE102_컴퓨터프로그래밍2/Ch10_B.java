import java.util.*;

public class Ch10_B  {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        //make accounts
        Account[] accounts = new Account[10];
        for(int i = 0; i < 10; i++) {
            accounts[i] = new Account(i, 100);
        }

        //program starts
        while(true) {
            System.out.print("Enter an id: ");

            long id1 = sc.nextLong();

            //catch exceptions on id input stage
            if(id1 == -20150901) {
                System.out.print("Exit code entered");
                return;
            }
            int id = (int)id1;

            if(id > 9 || id < 0) {
                System.out.println("Please enter a correct id");
                continue;
            }


            while(true) {
                print_menu();

                int choice;
                System.out.print("Enter a choice: ");
                choice = sc.nextInt();

                switch(choice) {
                    case 1:
                        System.out.printf("The balance is %.1f\n", accounts[id].balance);
                        break;

                    case 2:
                        System.out.print("Enter an amount to withdraw: ");
                        int withdraw_amount = sc.nextInt();


                        if(withdraw_amount <= accounts[id].balance) { accounts[id].balance -= withdraw_amount; }
                        else { System.out.println("The amount is too large, ignored"); }
                        break;

                    case 3:
                        System.out.print("Enter an amount to deposit: ");
                        int deposit_amount = sc.nextInt();
                        if(deposit_amount < 0) { System.out.println("The amount is negative, ignored"); }
                        else { accounts[id].balance += deposit_amount; }
                        break;

                    case 4:
                        System.out.println();
                        break;

                    default:
                        System.out.println("Wrong choice, try again: ");
                        break;
                }

                if(choice == 4) break;
            }
        }
    }

    static void print_menu() {
        System.out.println("\nMain menu");
        System.out.println("1: check balance");
        System.out.println("2: withdraw");
        System.out.println("3: deposit");
        System.out.println("4: exit");
        return;
    }
}
/*
class Account {
    int id;
    double balance;
    static double annualInterestRate;
    Date dateCreated;

    Account() { };

    Account(int id, double balance) {
        this.id = id;
        this.balance = balance;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getBalance() {
        return balance;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public double getAnnualInterestRate() {
        return annualInterestRate;
    }

    public static void setAnnualInterestRate(double annuallInterestRate) {
        annualInterestRate = annuallInterestRate;
    }

    public Date getDateCreated() {
        return dateCreated;
    }

    double getMonthlyInterestRate() {
        return (annualInterestRate / 100) / 12;
    }

    double getMonthlyInterest() {
        return balance * getMonthlyInterestRate();
    }

    void withdraw(double amount) {
        if(balance > amount) { balance = balance - amount; }
    }

    void deposit(double amount) {
        balance = balance + amount;
    }


}*/


