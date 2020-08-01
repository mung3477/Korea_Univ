import java.util.*;

public class Ch9_B {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        Stock stock = new Stock(sc.nextLine(), sc.nextLine());
        stock.setPreviousClosingPrice(sc.nextDouble());
        stock.setCurrentPrice(sc.nextDouble());

        System.out.printf("Prev Price: %.2f\n", stock.getPreviousClosingPrice());
        System.out.printf("Curr Price: %.2f\n", stock.getCurrentPrice());
        System.out.printf("Price Change: %.2f%%\n", stock.getChangePercent() * 100);
    }
}

class Stock {
    String id;
    String name;
    double previousClosingPrice;
    double currentPrice;

    public void setPreviousClosingPrice(double previousClosingPrice) {
        this.previousClosingPrice = previousClosingPrice;
    }

    public void setCurrentPrice(double currentPrice) {
        this.currentPrice = currentPrice;
    }

    public Stock(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public double getPreviousClosingPrice() {
        return previousClosingPrice;
    }

    public double getCurrentPrice() {
        return currentPrice;
    }

    public double getChangePercent() {
        return currentPrice / previousClosingPrice - 1;
    }

}