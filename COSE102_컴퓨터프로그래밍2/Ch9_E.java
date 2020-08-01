import java.util.*;

public class Ch9_E {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        Account account = new Account(sc.nextInt(), sc.nextInt());
        Account.setAnnualInterestRate(sc.nextDouble());

        System.out.printf("Balance : %.2f\n", account.getBalance());
        System.out.printf("Monthly interest : %.2f\n", account.getMonthlyInterest());

        account.withdraw(sc.nextDouble());

        System.out.printf("Balance : %.2f\n", account.getBalance());
        System.out.printf("Monthly interest : %.2f\n", account.getMonthlyInterest());

        account.deposit(sc.nextDouble());

        System.out.printf("Balance : %.2f\n", account.getBalance());
        System.out.printf("Monthly interest : %.2f\n", account.getMonthlyInterest());
    }
}

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


}