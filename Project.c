#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum category { mobilephone, mobileaccessories, laptops, electronic , games, home};
enum payment { BNPL, COD, Debit, Credit, NetBanking, UPI, PhonePe};
typedef struct Node { 
    char name[100];
    int cost;
    enum category cat;
    int available; 
    struct Node* next; 
}pNode;

typedef struct Customer
{
	char name[50];
	char phone[15];
	int Consumer_Id;
	enum payment pay;
	char email[100];
	char address[100];
	char *wishlist[14];
	char *purchase[50];
	char *favorite[14];
	struct Customer *next;

}cNode;

pNode *product=NULL;
cNode *customer=NULL;

char *productcat[] = {
	"Mobile Phones",
	"Mobile Accessories",
	"Laptops",
	"Electronic Gadgets",
	"Gaming Consoles", 
	"Home Appliances"
};

char *customerpay[] = {
	"Buy Now Pay Later",
	"Cash on Delivery",
	"Debit Card",
	"Credit Card",
	"Net Banking",
	"UPI Transaction",
	"PhonePe"
};

void printproduct(pNode *product)
{
	pNode *temp = product;
	printf("Product Name:\t");
	printf("Product Price\t");
	printf("Product Category:\t\n");
	while(temp!=NULL)
	{
		
		if(temp->available!=0)
		{
			
			printf("%s(%d)\t\t",temp->name,temp->available);
			printf("%d\t\t",temp->cost);
			printf("%s\n",productcat[temp->cat]);
		}
		temp = temp->next;
	}

}

void printcustomer(char name[], int Consumer_Id)
{
	cNode *temp = customer;
	int flag=0;
	while(temp!=NULL)
	{
		if(strcmp(temp->name,name)==0&&Consumer_Id==temp->Consumer_Id)
		{
			printf("Name. %s\n",temp->name);
			printf("Mobile No. %s\n",temp->phone);
			printf("Address. %s\n",temp->address);
			printf("Consumer_Id. %d\n",temp->Consumer_Id);
			printf("Payment Option- %s\n",customerpay[temp->pay]);

			int i=0;
			printf("WishList:\n");
			while(temp->wishlist[i]!=NULL)
			{
				printf("%s\n",temp->wishlist[i]);
				i++;
			}
			i=0;
			printf("Purchased:\n");
			while(temp->purchase[i]!=NULL)
			{
				printf("%s\n",temp->purchase[i]);
				i++;
			}
			i=0;
			printf("Favorite Purchases\n");
			while(temp->favorite[i]!=NULL)
			{
				printf("%s\n",temp->favorite[i]);
				i++;
			}
			flag=1;
		}
		temp=temp->next;
	}
	if(flag==0)
	{
		printf("Customer Not Found.\n");
	}
}


int checkproduct(char productname[], int q)				//check for product in stock and list
{	
	pNode *temp=product;
	while(temp)
	{
		if(strcmp(temp->name,productname)==0)
		{
			if(temp->available>=q)
				return 1;
			else
			{	
				printf("Product not available\n");
				return 0;
			}
		}
		temp=temp->next;
	}
	printf("Product not in list\n");
	return 0;
}

void setfavourite(char name[],char product[])			//sets the favorite list with customer name and new purchased product if product is purchased more than once
{
	cNode *temp=customer;
	
	while(temp)
	{	
		int n=0;
		if(strcmp(temp->name,name)==0)
		{	
			int count=0;
			while(temp->purchase[n])
			{
				if(strcmp(temp->purchase[n],product)==0)
				{
					count++;
				}
				n++;
			}
			if(count>1)
			{	
				int j=0,flag=0;
				while(temp->favorite[j])
				{
					if(strcmp(temp->favorite[j],product)==0)
						flag=1;
					j++;
				}
				if(flag==0)
				{
					temp->favorite[j] = malloc(100*sizeof(char));
					strcpy(temp->favorite[j],product);
				}
			}
			// printf("%s\n",temp->favorite[0]);
		}
		temp=temp->next;
	}
}



void printwishlist(int Consumer_Id)
{
	cNode *temp=customer;
	while(temp)
	{
		if(temp->Consumer_Id==Consumer_Id)
		{
			int n=0;
			printf("Wish list of %s is:\n",temp->name);
			while(temp->wishlist[n])
			{
				printf("%s\n",temp->wishlist[n++]);
			}
		}
		temp=temp->next;
	}
}

void AddWishList(int Consumer_Id, char productname[])			//add product to wishlist
{
	cNode *temp=customer;
	while(temp)
	{
		if(temp->Consumer_Id==Consumer_Id)
		{
			int n=0,flag=0;
			while(temp->wishlist[n]&&flag==0)
			{
				if(strcmp(temp->wishlist[n],productname)==0)
				{
					flag=1;
				}
				n++;
			}
			if(flag==1)
			{
				printf("Product already in wish list\n");
			}
			else
			{
				temp->wishlist[n]=malloc(100*sizeof(char));
				strcpy(temp->wishlist[n],productname);
			}
		}
		temp=temp->next;
	}
	printwishlist(Consumer_Id);
}






void ReturnProduct(int Consumer_Id, char productname[])		//returns product updates availability and shifts the array of purchases
{
	cNode *temp=customer;
	pNode *p=product;
	while(temp)
	{
		if(temp->Consumer_Id==Consumer_Id)
		{	
			int n=0,flag=0;
			while(temp->purchase[n]&&flag==0)
			{
				if(strcmp(temp->purchase[n],productname)==0)
				{
					// printf("%s\n",temp->purchase[n]);
					temp->purchase[n]=NULL;
					// printf("%s\n",temp->purchase[n]);
					flag=1;
					while(p)
					{
						if(strcmp(p->name,productname)==0)
						{
							p->available = p->available + 1;
							printf("CashBack of Amount %d through %s\n",p->cost,customerpay[temp->pay]);
						}
						p=p->next;
					}
					char *tempchar = temp->purchase[n];
					int j=n;
					while(temp->purchase[j+1])
					{
						temp->purchase[j]=temp->purchase[j+1];
						j++;
					}
					temp->purchase[j]=tempchar;
				}
				n++;
			}
			printcustomer(temp->name, temp->Consumer_Id);
		}
		temp=temp->next;
	}
}


void reduceavailable(char productname[])			//to reduce available of products
{
	pNode *temp=product;

	while(temp!=NULL)
	{
		if(strcmp(temp->name,productname)==0)
		{			
			temp->available=temp->available -1;
			// printf("%d\n",temp->available);
			break;
		}
	
			
		// printf("%d\n",temp->available);
		temp=temp->next;
	}
}

void createuser()
{
	cNode *temp = customer;
	int cindex=0;
	while(temp)
	{	
		cindex++;
		temp=temp->next;
	}
	cNode *cnew=(cNode*)malloc(sizeof(cNode));
	cnew->next = customer;
	customer = cnew;
	printf("Enter the name of user\n");
	char name[50];
	scanf("%s",name);
	strcpy(customer->name,name);
	printf("Enter mobile number\n");
	char mobile[10];
	scanf("%s",mobile);
	strcpy(customer->phone,mobile);
	printf("Enter the address\n");
	char address[100];
	scanf("%s",address);
	strcpy(customer->address,address);
	printf("Enter email id\n");
	char email[20];
	scanf("%s",email);
	strcpy(customer->email,email);
	for(int i=0;i<7;i++)
	{
		printf("%d. %s\n",(i+1),customerpay[i]);
	}
	printf("Enter the payment mode number\n");
	int index;
	scanf("%d",&index);
	enum payment ptemp = index-1;
	customer->pay = ptemp;
	customer->Consumer_Id = cindex;
	// printcustomer(customer->name, customer->Consumer_Id);
	printf("User Created Successfully!\n");
}

void Order()
{
	printf("Enter 1 for Create a new user\n Enter 2 for choose existing consumer\n");
	int choice; 
	scanf("%d",&choice);
	if(choice==1)
	{
		createuser();
		char productname[50];
		printproduct(product);
		printf("Enter product name\n");
		scanf("%s",productname);
		printf("Enter the quantity\n");
		int q,check;
		scanf("%d",&q);
		check=checkproduct(productname,q);
		if(check)
		{
			for(int j=0;j<q;j++)
			{	
				int n=0;
				while(customer->purchase[n])
				{
					n++;
				}
				customer->purchase[n] = malloc(100*sizeof(char));
				strcpy(customer->purchase[n],productname);
				// printf("%s\n", customer->purchase[n]);
				reduceavailable(productname);
				setfavourite(customer->name, productname);
			}
		}
		printcustomer(customer->name, customer->Consumer_Id);				
	}
	else if(choice==2)
	{
		cNode *temp = customer;
		while(temp)
		{
			printf("%s\t",temp->name);
			printf("%d\n",temp->Consumer_Id);
			temp=temp->next;
		}
		char name[50];
		printf("Enter the name of user\n");
		scanf("%s",name);
		int id;
		printf("Enter counsumer id\n");
		scanf("%d",&id);
		temp=customer;
		while(temp)
		{
			if(strcmp(temp->name,name)==0&&id==temp->Consumer_Id)
			{
				char productname[50];
				printproduct(product);
				printf("Enter product name\n");
				scanf("%s",productname);
				printf("Enter the quantity\n");
				int q,check;
				scanf("%d",&q);
				check=checkproduct(productname,q);
				printf("Check = %d\n",check);
				if(check)
				{
					for(int j=0;j<q;j++)
					{	
						int n=0;
						while(temp->purchase[n])
						{
							n++;
						}
						temp->purchase[n] = malloc(100*sizeof(char));
						strcpy(temp->purchase[n],productname);
						// printf("%s\n", temp->purchase[n]);
						reduceavailable(productname);
						setfavourite(temp->name, productname);
					}
				}
				
				printcustomer(temp->name, temp->Consumer_Id);
			}
			temp=temp->next;
		}
	}

}

void customerpurchase()					//Decreasing order of frequency of purchases
{
	int index[10],n=0;
	char *names[10];
	cNode *temp=customer;
	while(temp)
	{
		int i=0;
		while(temp->purchase[i])
		{
			i++;
		}
		index[n]=i;
		names[n++]=temp->name;
		temp=temp->next;
	}

	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(index[j]<index[j+1])
			{
				int temp=index[j];
				index[j]=index[j+1];
				index[j+1]=temp;

				char *name = names[j];
				names[j]=names[j+1];
				names[j+1] = name;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		printf("%s",names[i]);
		printf("\t%d\n",index[i]);
	}

}

void productfreq()						//items purchased frequently by all customers condition: purchased atleast twice
{
	pNode *temp=product;
	printf("Frequently Purchased Items:\n");
	while(temp!=NULL)
	{
		if(temp->available<9)
		{
			printf("%s\n",temp->name);
		}
		temp=temp->next;
	}
	temp=product;
	printf("\nNot Frequently Purchased Items:\n");
	while(temp!=NULL)
	{
		if(temp->available==10||temp->available==9)
		{
			printf("%s\n",temp->name);
		}
		temp=temp->next;
	}
}


void customerfreq(char name[], int Consumer_Id)		//favorite purchases by a customer
{
	cNode *temp = customer;
	int flag=0;
	while(temp!=NULL)
	{
		if(strcmp(temp->name,name)==0&&Consumer_Id==temp->Consumer_Id)
		{
			printf("Favorite Purchases of %s are:\n",temp->name);
			int i=0;
			while(temp->favorite[i]!=NULL)
			{
				printf("%s\n",temp->favorite[i]);
				i++;
			}
			flag=1;
		}
		temp=temp->next;
	}
	if(flag==0)
	{
		printf("Customer Not Found.\n");
	}
}
main()
{
	pNode *ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = NULL;
	

	strcpy(ptemp->name,"iphone");
	ptemp->cost = 35000;
	ptemp->cat = mobilephone;
	ptemp->available = 10;
	product = ptemp;


	ptemp = (pNode*)malloc(sizeof(pNode));
	strcpy(ptemp->name,"oneplus");
	ptemp->cost = 30000;
	ptemp->cat = mobilephone;
	ptemp->available = 10;
	ptemp->next = product;
	product = ptemp;



	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;
	// free(ptemp);
	strcpy(product->name,"headphones");
	product->cost = 1000;
	product->cat = mobileaccessories;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"charger");
	product->cost = 500;
	product->cat = mobileaccessories;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"macbook");
	product->cost = 100000;
	product->cat = laptops;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"hp");
	product->cost = 50000;
	product->cat = laptops;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"camera");
	product->cost = 7000;
	product->cat = electronic;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"tablets");
	product->cost = 15000;
	product->cat = electronic;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"PS4");
	product->cost = 40000;
	product->cat = games;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"XBOX");
	product->cost = 32000;
	product->cat = games;
	product->available = 10;


	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"refrigerator");
	product->cost = 75000;
	product->cat = home;
	product->available = 10;



	ptemp = (pNode*)malloc(sizeof(pNode));
	ptemp->next = product;
	product = ptemp;

	strcpy(product->name,"washingmachine");
	product->cost = 25000;
	product->cat = home;
	product->available = 10;




	cNode *ctemp = (cNode*)malloc(sizeof(cNode));
	ctemp->next = NULL;
	customer = ctemp;

	strcpy(customer->name,"Umang");
	strcpy(customer->phone,"9764468006");
	strcpy(customer->address,"08A Raymond Shop");
	strcpy(customer->email,"umangd98@gmail.com");
	customer->pay = BNPL;
	customer->Consumer_Id = 0;
	customer->wishlist[0] = malloc(100*sizeof(char));
	strcpy(customer->wishlist[0],"iphone");
	customer->purchase[0] = malloc(100*sizeof(char));
	strcpy(customer->purchase[0], "camera");
	reduceavailable("camera");
	setfavourite(customer->name,customer->purchase[0]);
	customer->purchase[1] = malloc(100*sizeof(char));
	strcpy(customer->purchase[1], "camera");
	reduceavailable("camera");
	setfavourite(customer->name,customer->purchase[1]);


	ctemp = (cNode*)malloc(sizeof(cNode));
	ctemp->next = customer;
	customer = ctemp;

	strcpy(customer->name,"Akshansh");
	strcpy(customer->phone,"9823024724");
	strcpy(customer->address,"Rohini, Delhi");
	strcpy(customer->email,"akshansh@gmail.com");
	customer->pay = COD;
	customer->Consumer_Id = 1;
	customer->wishlist[0] = malloc(100*sizeof(char));
	strcpy(customer->wishlist[0],"oneplus");
	customer->purchase[0] = malloc(100*sizeof(char));
	strcpy(customer->purchase[0], "hp");
	reduceavailable("hp");
	setfavourite(customer->name,customer->purchase[0]);
	customer->purchase[1] = malloc(100*sizeof(char));
	strcpy(customer->purchase[1], "headphones");
	reduceavailable("headphones");
	setfavourite(customer->name,customer->purchase[1]);

	int flag=1, input;
	while(flag)
	{
		printf("Welcome to Online Store\n");
		printf("Enter 1 for Placing Order\n");
		printf("Enter 2 for Returning Order\n");
		printf("Enter 3 for printing customer info \n");
		printf("Enter 4 for Adding Wish list\n");
		printf("Enter 5 for Printing Wish List for a user\n");
		printf("Enter 6 for Printing product list of available products\n");
		printf("Enter 7 for Printing Items frequently purchased by a user\n");
		printf("Enter 8 for Printing Items frequently purchased by all users\n");
		printf("Enter 9 for printing List of customers decreasing order of purchases\n");
		scanf("%d",&input);

		switch(input)
		{
			case 1:
			{
				Order();
			}break;

			case 2:
			{
				int id2;
				printf("Enter Consumer_Id\n");
				scanf("%d",&id2);
				printf("Enter product name\n");
				char pname2[50];
				scanf("%s",pname2);
				ReturnProduct(id2, pname2);
			}break;

			case 3:
			{
				int id3;
				printf("Enter Consumer_Id\n");
				scanf("%d",&id3);
				printf("Enter consumer name\n");
				char cname3[50];
				scanf("%s",cname3);
				printcustomer(cname3,id3);
			}break;

			case 4:
			{
				int id4;
				printf("Enter Consumer_Id\n");
				scanf("%d",&id4);
				printproduct(product);
				printf("Enter product name\n");
				char pname4[50];
				scanf("%s",pname4);
				AddWishList(id4,pname4);
			}break;

			case 5:
			{
				int id5;
				printf("Enter Consumer Id\n");
				scanf("%d",&id5);
				printwishlist(id5);
			}break;

			case 6:
			{
				printproduct(product);
			}break;

			case 7:
			{
				int id7;
				printf("Enter Consumer_Id\n");
				scanf("%d",&id7);
				printf("Enter consumer name\n");
				char cname7[50];
				scanf("%s",cname7);
				customerfreq(cname7,id7);
			}break;

			case 8:
			{
				productfreq();
			}break;

			case 9:
			{
				customerpurchase();
			}
		}
	}




}