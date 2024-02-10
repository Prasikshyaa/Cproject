#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



// Storing customer information and cake details
struct CakeOrder {
    char name[20];
    char phone[20];
    char cake[20];
    char frosting[20];
    char toppings[20];
    char message[50];
    double pounds;
    double cakePrice;
    double frostingPrice;
    double toppingsPrice;
    double pricePerPound;
    double totalPrice;
    char status[10];
};

// Function to find the index of an option in an array
int findIndex(const char *option, const char *options[], int size);

// Function to make sure the user chooses valid option
char *getValidInput(const char *prompt, const char *options[], int size);

// Function to calculate the price of the cake
double calculateCakePrice(char *cake);
double calculateFrostingPrice(char *frosting);
double calculateToppingsPrice(char *toppings);
double calculateTotalPrice(struct CakeOrder *order);
void generateOrderStatus(char *status);
char *readStringFromUser(const char *prompt);
void saveOrderToFile(struct CakeOrder *order);
void displayOrderDetails(struct CakeOrder *order);

int main() {
    // Random number generation
    srand(time(NULL));

    // Defining cakeOrder structure
    struct CakeOrder order;

    // Asking for Customer information
    printf("Enter customer name: ");
    fgets(order.name, sizeof(order.name), stdin);
    order.name[strcspn(order.name, "\n")] = '\0';

    printf("Enter phone number: ");
    fgets(order.phone, sizeof(order.phone), stdin);
    order.phone[strcspn(order.phone, "\n")] = '\0';

    // Defining available options for cake, frosting, and toppings
    const char *cakeOptions[6] = {"Hazelnut", "Tiramisu", "chocolate", "vanilla", "blueberry cheesecake", "red velvet"};
    const char *frostingOptions[4] = {"cream cheese", "chocolate ganache", "whipped cream", "buttercream"};
    const char *toppingsOptions[4] = {"chocolate chips", "fresh fruits", "nuts", "sprinkles"};

    // Getting cake details with valid input
    order.cake[0] = '\0';
    while (findIndex(order.cake, cakeOptions, 6) == -1) {
        printf("What type of cake would you like? (Hazelnut, Tiramisu, chocolate, vanilla, blueberry cheesecake, red velvet): ");
        fgets(order.cake, sizeof(order.cake), stdin);
        order.cake[strcspn(order.cake, "\n")] = '\0';
        if (findIndex(order.cake, cakeOptions, 6) == -1) {
            printf("Sorry, '%s' is not available. Please choose a valid option.\n", order.cake);
        }
    }

    order.frosting[0] = '\0';
    while (findIndex(order.frosting, frostingOptions, 4) == -1) {
        printf("Enter frosting (cream cheese, chocolate ganache, whipped cream, buttercream): ");
        fgets(order.frosting, sizeof(order.frosting), stdin);
        order.frosting[strcspn(order.frosting, "\n")] = '\0';
        if (findIndex(order.frosting, frostingOptions, 4) == -1) {
            printf("Sorry, '%s' is not available. Please choose a valid option.\n", order.frosting);
        }
    }

    order.toppings[0] = '\0';
    while (findIndex(order.toppings, toppingsOptions, 4) == -1) {
        printf("Enter toppings (chocolate chips, fresh fruits, nuts, sprinkles): ");
        fgets(order.toppings, sizeof(order.toppings), stdin);
        order.toppings[strcspn(order.toppings, "\n")] = '\0';
        if (findIndex(order.toppings, toppingsOptions, 4) == -1) {
            printf("Sorry, '%s' is not available. Please choose a valid option.\n", order.toppings);
        }
    }

    // Asking additional cake order details
    printf("Enter message you want to write on the cake: ");
    fgets(order.message, sizeof(order.message), stdin);
    order.message[strcspn(order.message, "\n")] = '\0';

    printf("How many pounds of cake would you like?: ");
    scanf("%lf", &order.pounds);

    // Calculate the total price of the cake order
    order.totalPrice = calculateTotalPrice(&order);

    // Generate a random order status
    generateOrderStatus(order.status);

    // Save the cake order to a file
    saveOrderToFile(&order);

    // Display the cake order details
    displayOrderDetails(&order);

    return 0;
}

// Function to find the index of an option in an array
int findIndex(const char *option, const char *options[], int size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(option, options[i]) == 0) {
            return i;
        }
    }
    return -1; // Option not found
}

// Function to get valid input from the user
char *getValidInput(const char *prompt, const char *options[], int size) {
    char buffer[256];
    do {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
        if (findIndex(buffer, options, size) == -1) {
            printf("Sorry, '%s' is not available. Please choose a valid option.\n", buffer);
        } else {
            return strdup(buffer);
        }
    } while (1); // Loop until a valid input is provided
}

// Function to calculate the price of the cake
double calculateCakePrice(char *cake) {
    const char *cakeOptions[6] = {"Hazelnut", "Tiramisu", "chocolate", "vanilla", "blueberry cheesecake", "red velvet"};
    double cakePrices[6] = {15.0, 16.0, 12.0, 10.0, 22.0, 20.0};
    int cakeIndex = findIndex(cake, cakeOptions, 6);
    return (cakeIndex != -1) ? cakePrices[cakeIndex] : 0.0;
}

// Function to calculate the price of frosting
double calculateFrostingPrice(char *frosting) {
    const char *frostingOptions[4] = {"cream cheese", "chocolate ganache", "whipped cream", "buttercream"};
    double frostingPrices[4] = {5.0, 7.0, 3.0, 4.0};
    int frostingIndex = findIndex(frosting, frostingOptions, 4);
    return (frostingIndex != -1) ? frostingPrices[frostingIndex] : 0.0;
}

// Function to calculate the price of toppings
double calculateToppingsPrice(char *toppings) {
    const char *toppingsOptions[4] = {"chocolate chips", "fresh fruits", "nuts", "sprinkles"};
    double toppingsPrices[4] = {3.0, 4.0, 1.5, 2.0};

    // Copy of toppings string
    char *toppingsCopy = strdup(toppings);

    double totalToppingsPrice = 0.0;
    char *token = strtok(toppingsCopy, ",");
    while (token != NULL) {
        int toppingsIndex = findIndex(token, toppingsOptions, 4);
        if (toppingsIndex != -1) {
            totalToppingsPrice += toppingsPrices[toppingsIndex];
        }
        token = strtok(NULL, ",");
    }
    // Free the allocated memory for the copy
    free(toppingsCopy);

    return totalToppingsPrice;
}

// Function to calculate the total price
double calculateTotalPrice(struct CakeOrder *order) {
    // Price of cake per pound
    order->pricePerPound = 8.0;

    // Calculate prices individually
    order->cakePrice = calculateCakePrice(order->cake);
    order->frostingPrice = calculateFrostingPrice(order->frosting);
    order->toppingsPrice = calculateToppingsPrice(order->toppings);

    // Calculate the total price
    return (order->pricePerPound * order->pounds) + order->cakePrice + order->frostingPrice + order->toppingsPrice;
}

// Function to randomly generate order status
void generateOrderStatus(char *status) {
    // Array of possible statuses
    const char *orderStatuses[2] = {"pending", "delivered"};

    // Generate a random index either 0 or 1
    int randomIndex = rand() % 2;

    // Copy the randomly chosen order status to provide status variable
    strcpy(status, orderStatuses[randomIndex]);
}

// Function to save order to a file
void saveOrderToFile(struct CakeOrder *order) {
    FILE *file = fopen("orders.txt", "a"); // Open file in append mode

    if (file != NULL) {
        // Write order data to file
        fprintf(file, "Customer Name: %s\n", order->name);
        fprintf(file, "Phone Number: %s\n", order->phone);
        fprintf(file, "Cake Flavor: %s ($%.2lf)\n", order->cake, order->cakePrice);
        fprintf(file, "Frosting: %s ($%.2lf)\n", order->frosting, order->frostingPrice);
        fprintf(file, "Toppings: %s ($%.2lf)\n", order->toppings, order->toppingsPrice);
        fprintf(file, "Message on Cake:%s\n", order->message);
        fprintf(file, "Pounds of Cake: $%.2lf\n", order->pounds);
        fprintf(file, "Total Price: $%.2lf\n", order->totalPrice);
        fprintf(file, "Order Status: %s\n", order->status);
        fprintf(file, "------------------------------------------\n");

        fclose(file); // Close the file
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

// Function to display order details
void displayOrderDetails(struct CakeOrder *order) {
    printf("\nOrder Details:\n");
    printf("Customer Name: %s\n", order->name);
    printf("Phone Number: %s\n", order->phone);
    printf("Cake Flavor: %s ($%.2lf)\n", order->cake, order->cakePrice);
    printf("Frosting: %s ($%.2lf)\n", order->frosting, order->frostingPrice);
    printf("Toppings: %s ($%.2lf)\n", order->toppings, order->toppingsPrice);
    printf("Message on cake: %s\n", order->message);
    printf("Pounds of Cake: %.2lf\n", order->pounds);
    printf("Total Price: $%.2lf + $%.2lf + $%.2lf + (%.2lf * $8) = $%.2lf\n", order->cakePrice, order->frostingPrice, order->toppingsPrice, order->pounds, order->totalPrice);
    printf("Order Status: %s\n", order->status);
}
