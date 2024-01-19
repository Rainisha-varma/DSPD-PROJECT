#include<stdio.h>
#include<string.h>
#include<math.h>
typedef struct food
{
    char name[50];
    int price;
    int serv_tym;
}food;
typedef struct food_order
{
   char name[50];
   int quantity;
   int price;
   int serv_tym;
}food_order;
typedef struct full_address
{
    char area[100];
    int address_plot;
    int address_x;
    int address_y;
}full_address;
typedef struct restaurant
{
    char name[50];
    full_address address;
    int generalItemNum;
    food general[10];
    int splItemNum;
    food spl_item[4];
    food itemOfTheDay;
}restaurant;
typedef struct order
{
    char user_name[50];
    int order_time;
    int types_of_foods;
    food_order food[30];
    full_address user_address;
    long long int phn_no;
}order;
float distance(int x1,int y1,int x2,int y2) {
    int x,y;
    float z;
    x=x2-x1;
    y=y2-y1;
    int a=pow(x,2);
    int b=pow(y,2);
    z=a+b;
    int d=pow((a+b),0.5);
    return d;
}
//first function getMinTime
void getMinTime(char item[], int quantity, restaurant R[], full_address user_address, int res) {
     int i,j,flag=0;
     int min=36000;
     int delivery_tym,time;
     float d;
     restaurant min_res;
     food min_f;
     for(i=0;i<res;i++) {
        flag=0;
        for(j=0;j<R[i].generalItemNum && flag==0;j++) {
             if(strcmp(item,R[i].general[j].name)==0) {
                   d=distance(R[i].address.address_x,R[i].address.address_y,user_address.address_x,user_address.address_y);
  delivery_tym=d/30;      //here 30 is avg speed of motor bike in m per min
  time=delivery_tym+(R[i].general[j].serv_tym)*quantity;
  flag=1;
  if (time<min) {
       restaurant min_res = R[i];
       min=time;
       food min_f=R[i].itemOfTheDay;
  }
  }
  }
        for(j=0;j<R[i].splItemNum && flag==0;j++) {
             if(strcmp(item,R[i].spl_item[j].name)==0) {
                   d=distance(R[i].address.address_x,R[i].address.address_y,user_address.address_x,user_address.address_y);
  delivery_tym=d/100;      //here 100 is avg speed of motor bike in m per min
  time=delivery_tym+(R[i].spl_item[j].serv_tym)*quantity;
  flag=1;
  if (time<min) {
       restaurant min_res = R[i];
       min=time;
       food min_f=R[i].itemOfTheDay;
  }
  }
  }    
  if(strcmp(item,R[i].itemOfTheDay.name)==0) {
  d=distance(R[i].address.address_x,R[i].address.address_y,user_address.address_x,user_address.address_y);
  delivery_tym=d/100;      //here 100 is avg speed of motor bike in m per min
  time=delivery_tym+(R[i].itemOfTheDay.serv_tym)*quantity;
  if (time<min) {
       restaurant min_res = R[i];
       food min_f=R[i].itemOfTheDay;
       min=time;
  }
  }
  }
  if(min==36000) {
      printf("Sorry, This item is currently not available");
  }
  else {
      printf("\n");
      printf("The Item is available in least time at\n");
      printf("%s\n",min_res.name);
      printf("which is at %s\n",min_res.address.area);
      printf("with a price of %d\n",min_f.price);
      printf("within a time of %d min\n",min);
  }
  }
  void getItemAvailability(char item[],restaurant R[], int res) {
     int i,j,flag=0;
     int check=0;
     for(i=0;i<res;i++) {
       flag=0;
       for(j=0;j<R[i].generalItemNum && flag==0;j++) {
           if(strcmp(item,R[i].general[j].name)==0) {
            printf("Available in %s at %d rate\n",R[i].name,R[i].general[j].price);
            flag=1;
            check=1;
           }
       }
       for(j=0;j<R[i].splItemNum && flag==0;j++) {
           if(strcmp(item,R[i].spl_item[j].name)==0) {
            printf("Available in %s at %d rate\n",R[i].name,R[i].spl_item[j].price);
            flag=1;
            check=1;
           }
       }
       if(strcmp(item,R[i].itemOfTheDay.name)==0) {
            printf("Available in %s at %d rate\n",R[i].name,R[i].spl_item[j].price);
            check=1;
       }
       
     }
     if(check==0) printf("Sorry this item is not available\n");
   }
   int partition_strings(char array[][50],int low,int high,char x[]) {
        int i,j;
        char temp[50];
        i=low;
        j=high;
        while(i<j && strcmp(array[i],x)<=0) 
            i++;
        while(i<j && strcmp(array[j],x)>0)
            j--;
        if(strcmp(array[j],x)>0) 
            j=j-1;
        while(i<j) {
           strcpy(temp,array[i]);
           strcpy(array[i],array[j]);
           strcpy(array[j],temp);
           i++;
           j--;
           while(strcmp(array[i],x)<=0)
               i++;
           while(strcmp(array[j],x)>0)   
               j--;
           }
        return j;
     }
    void qsort_strings(char array[][50],int low,int high) {
       int p;
         char temp[50];
         if(low<high){
            p=partition_strings(array,low,high,array[low]);
            strcpy(temp,array[p]);
            strcpy(array[p],array[low]);
            strcpy(array[low],temp);
            qsort_strings(array,low,p-1);
            qsort_strings(array,p+1,high);
         }
     }
   //partition funf for restaurants
    int partition_of_res(restaurant R[],int low,int high,char x[]) {
        int i,j;
        restaurant temp;
        i=low;
        j=high;
        while(i<j && strcmp(R[i].name,x)<=0) 
            i++;
        while(i<j && strcmp(R[j].name,x)>0)
            j--;
        if(strcmp(R[j].name,x)>0) 
            j=j-1;
        while(i<j) {
           temp=R[i];
           R[i]=R[j];
           R[j]=temp;
           i++;
           j--;
           while(strcmp(R[i].name,x)<=0)
               i++;
           while(strcmp(R[j].name,x)>0)   
               j--;
           }
        return j;
     }
     //quicksort for restaurant names
     void qsort_res(restaurant R[],int low,int high) {
         int p;
         restaurant temp;
         if(low<high){
            p=partition_of_res(R,low,high,R[low].name);
            temp=R[p];
            R[p]=R[low];
            R[low]=temp;
            qsort_res(R,low,p-1);
            qsort_res(R,p+1,high);
         }
     }
     //partition funf for food items
     int partition_of_food(food F[],int low,int high,char x[]) {
          int i,j;
        food temp;
        i=low;
        j=high;
        while(i<j && strcmp(F[i].name,x)<=0) 
            i++;
        while(i<j && strcmp(F[j].name,x)>0)
            j--;
        if(strcmp(F[j].name,x)>0) 
            j=j-1;
        while(i<j) {
           temp=F[i];
           F[i]=F[j];
           F[j]=temp;
           i++;
           j--;
           while(strcmp(F[i].name,x)<=0)
               i++;
           while(strcmp(F[j].name,x)>0)   
               j--;
           }
        return j;
     }
     //quick sort for food items
     void qsort_food(food F[],int low,int high) {
         int p;
         food temp;
         if(low<high){
            p=partition_of_food(F,low,high,F[low].name);
            temp=F[p];
            F[p]=F[low];
            F[low]=temp;
            qsort_food(F,low,p-1);
            qsort_food(F,p+1,high);
         }
     }  
     void getItemListInSortedOrder(char name[],restaurant R[], int res) {
        int i,j,flag=0;
        int z;
        for(i=0;i<res && flag==0;i++) {
            if(strcmp(name,R[i].name)==0) {
               flag=1;
               }
        }
        z=i-1;
        int total=R[z].generalItemNum+R[z].splItemNum+1;
        food allFoods[total];
        for(j=0;j<R[z].generalItemNum;j++) {
            allFoods[j]=R[z].general[j];
        }
        for(j=R[z].generalItemNum;j<total-1;j++) {
           allFoods[j]=R[z].spl_item[j-R[z].generalItemNum];
        }
        allFoods[j]=R[z].itemOfTheDay;
        qsort_food(allFoods,0,total-1);
        printf("The list of items in %s restaurant are:\n",R[z].name);
        for(j=0;j<total;j++) {
             printf("%s at %d rupees\n",allFoods[j].name,allFoods[j].price);
        }
    }
    void getItemListInAreaSortedOrder(char area_need[],restaurant R[],int res) {
        int i,j,k=0;
        
        restaurant temp_R[res];
        for(i=0;i<res;i++) {
            if(strcmp(area_need,R[i].address.area)==0) {
               temp_R[k]=R[i];
               k++;
               }
        }
        printf("The restaurants in %s area and food items available in it are:\n",area_need);
        for(i=0;i<k;i++) {
            printf("%s\n",temp_R[i].name);
            getItemListInSortedOrder(temp_R[i].name,temp_R,k+1);
        }
     }
     void getAllSpecialItemListInOrder(restaurant R[],int res,char input_R[][50],int input_res) {
          int i,j,k,flag=0;
          for(i=0;i<input_res;i++) {
              flag=0;
              for(j=0;j<res && flag==0;j++) {
                 if(strcmp(input_R[i],R[j].name)==0) {
                    flag=1;
                    printf("%s at %s\n",R[j].name,R[j].address.area);
                    qsort_food(R[j].spl_item,0,(R[j].splItemNum-1));
                    printf("The special items are\n");
                    for(k=0;k<R[j].splItemNum;k++) {
                       printf("%s at %d rupees\n",R[j].spl_item[k].name,R[j].spl_item[k].price);
                    }
                 }
              }
           }
       }
       void getItemOfDayListInSortedOrder(char area_need[],restaurant R[],int res) {
        int i,j,k=0;
        restaurant temp_R[res];
        for(i=0;i<res;i++) {
            if(strcmp(area_need,R[i].address.area)==0) {
               temp_R[k]=R[i];
               k++;
               }
         }
         food items_of_the_day[k];
         for(i=0;i<k;i++) {
            items_of_the_day[i]=temp_R[i].itemOfTheDay;
         }
         qsort_food(items_of_the_day,0,k-1);
         printf("The items of the day in the area %s are",area_need);
         for(i=0;i<k;i++) {
             printf("%s at %d rupees\n",items_of_the_day[i].name,items_of_the_day[i].price);
         }
        }
    int commonAndUnique(restaurant input_R[],int input_res,char commonitems[][50],char uniqueitems[][50],int UorC){
    char combined[100][50];
    int i,j,unique=0;
    int cnt,common=0;
    int total=0;
    for(i=0;i<input_res;i++) {
        for(j=0;j<input_R[i].generalItemNum;j++) {
            strcpy(combined[total],input_R[i].general[j].name);
            total++;
        }
        for(j=0;j<input_R[i].splItemNum;j++) {
            strcpy(combined[total],input_R[i].spl_item[j].name);
            total++;
        }
        strcpy(combined[total],input_R[i].itemOfTheDay.name);
        total++;
    }
    for(i=0;i<total;i++) {
        cnt=0;
         for(j=0;j<total;j++) {
             if(strcmp(combined[i],combined[j])==0) {
                 cnt++;
             }
         }
         if(cnt==input_res) {
               strcpy(commonitems[common],combined[i]);
               common++;
         }
         else if(cnt==1) {
               strcpy(uniqueitems[unique],combined[i]);
               unique++;
         }
    }
    if(UorC==0) return unique;
    else return common;
}
 void getCommonItem(char list[][50],int input_list,restaurant R[],int res) {
    int i,j,k=0;
    int l=0;
    int flag;
    restaurant temp_R[input_list];
    char commonitems[100][50];
    char uniqueitems[100][50];
    int p,UorC=1;
    for(i=0;i<input_list;i++) {
              flag=0;
              for(j=0;j<res && flag==0;j++) {
                 if(strcmp(list[i],R[j].name)==0) {
                    flag=1;
                    temp_R[k]=R[j];
                    k++;
                 }
              }
           }
    p=commonAndUnique(temp_R,input_list,commonitems,uniqueitems,UorC);
    qsort_strings(commonitems,0,p-1);
    for(i=0;i<p;i++) {
        flag=0;
        printf("%s\n",commonitems[i]);
        for(j=0;j<input_list;j++) {
            flag=0;
          for(l=0;l<temp_R[j].generalItemNum && flag==0;l++){
            if(strcmp(commonitems[i],temp_R[j].general[l].name)==0) {
                flag=1;
                printf("in %s at %d\n",temp_R[j].name,temp_R[j].general[l].price);
            }
          }
          for(l=0;l<temp_R[j].splItemNum && flag==0;l++){
            if(strcmp(commonitems[i],temp_R[j].spl_item[l].name)==0) {
                flag=1;
                printf("in %s at %d\n",temp_R[j].name,temp_R[j].spl_item[l].price);
            }
          }
          if(flag==0 && strcmp(commonitems[i],temp_R[j].itemOfTheDay.name)==0) {
              flag=1;
              printf("in %s at %d\n",temp_R[j].name,temp_R[j].itemOfTheDay.price);
          }
        }
    }
}
void getUniqueItem(char list[][50],int input_list,restaurant R[],int res) {
    int i,j,k=0;
    int l=0;
    int flag;
    restaurant temp_R[input_list];
    char commonitems[100][50];
    char uniqueitems[100][50];
    int p,UorC=0;
    for(i=0;i<input_list;i++) {
              flag=0;
              for(j=0;j<res && flag==0;j++) {
                 if(strcmp(list[i],R[j].name)==0) {
                    flag=1;
                    temp_R[k]=R[j];
                    k++;
                 }
              }
           }
    p=commonAndUnique(temp_R,input_list,commonitems,uniqueitems,UorC);
    qsort_strings(uniqueitems,0,p-1);
    for(i=0;i<p;i++) {
        flag=0;
        printf("%s\n",uniqueitems[i]);
        for(j=0;j<input_list && flag==0;j++) {
          for(l=0;l<temp_R[j].generalItemNum && flag==0;l++){
            if(strcmp(uniqueitems[i],temp_R[j].general[l].name)==0) {
                flag=1;
                printf("in %s at %d\n",temp_R[j].name,temp_R[j].general[l].price);
            }
          }
          for(l=0;l<temp_R[j].splItemNum && flag==0;l++){
            if(strcmp(uniqueitems[i],temp_R[j].spl_item[l].name)==0) {
                flag=1;
                printf("in %s at %d\n",temp_R[j].name,temp_R[j].spl_item[l].price);
            }
          }
          if(flag==0 && strcmp(uniqueitems[i],temp_R[j].itemOfTheDay.name)==0) {
              flag=1;
              printf("in %s at %d\n",temp_R[j].name,temp_R[j].itemOfTheDay.price);
          }
        }
    }
}   
    void placeAnOrder(food_order wishToEat[],int items_no,full_address user_address,int ordernum,restaurant R[],int res) {
    int delivery_tym,serve_time;
    int i,j,flag=0;
    float d;
    restaurant theRes;
    char resNeed[50];
    printf("These are the restaurants that are available to you\n");
    for(i=0;i<res;i++) {
        printf("%s\n",R[i].name);
    }
    printf("Choose one of the above\n");
    getchar();
    fgets(resNeed,50,stdin);
    for(i=0;i<res && flag==0;i++) {
        if(strcmp(R[i].name,resNeed)==0) {
            flag=1;
            theRes=R[i];
        }
    }
    int check=0;
    int cost=0;
   d=distance(theRes.address.address_x,theRes.address.address_y,user_address.address_x,user_address.address_y);
   delivery_tym=d/30;
   serve_time=delivery_tym;
   for(i=0;i<items_no && check==0;i++) {
       flag=0;
       for(j=0;j<theRes.generalItemNum && flag==0;j++) {
           if(strcmp(theRes.general[j].name,wishToEat[i].name)==0) {
               flag=1;
               serve_time=serve_time+(theRes.general[j].serv_tym*wishToEat[i].quantity);
               cost=cost+theRes.general[j].price*wishToEat[i].quantity;
           }
       }
       for(j=0;j<theRes.splItemNum && flag==0;j++) {
           if(strcmp(theRes.spl_item[j].name,wishToEat[i].name)==0) {
               flag=1;
               serve_time=serve_time+(theRes.spl_item[j].serv_tym*wishToEat[i].quantity);
               cost=cost+theRes.spl_item[j].price*wishToEat[i].quantity;;
           }
       }
       if(flag==0 && strcmp(theRes.itemOfTheDay.name,wishToEat[i].name)==0) {
        flag=1;
        serve_time=serve_time+(theRes.itemOfTheDay.serv_tym*wishToEat[i].quantity);
        cost=cost+theRes.itemOfTheDay.price*wishToEat[i].quantity;;
       }
       if(flag==0) {
           check=1;
           printf("Sorry these items are not available in this partivular restaurant\n");
       }
   }
   printf("Your Order Id is FoodULove%d\n",ordernum);
   printf("You will receive your orderin %d min and total cost is %d\n",serve_time,cost);
}
         
    void main() {
       restaurant R[8];
    //Restaurants
    strcpy(R[0].name,"Anna The Restaurant\n");
    strcpy(R[1].name,"Biryani Street\n");
    strcpy(R[2].name,"Burger It Up\n");
    strcpy(R[3].name,"Cafe Seven O' Eleven\n");
    strcpy(R[4].name,"Chef's Kitchen\n");
    strcpy(R[5].name,"Delish Kitchen\n");
    strcpy(R[6].name,"Pink Berry Cakes\n");
    strcpy(R[7].name,"The Hot Chinese\n");
    //addresses
    strcpy(R[0].address.area,"Bajaj Nagar\n");
    strcpy(R[1].address.area,"Lakadganj\n");
    strcpy(R[2].address.area,"Higna T point\n");
    strcpy(R[3].address.area,"Bajaj Nagar\n");
    strcpy(R[4].address.area,"Lakadganj\n");
    strcpy(R[5].address.area,"Higna T point\n");
    strcpy(R[6].address.area,"Bajaj Nagar\n");
    strcpy(R[7].address.area,"Chaoni\n");
    //address plots
    R[0].address.address_plot=25;
    R[1].address.address_plot=64;
    R[2].address.address_plot=18;
    R[3].address.address_plot=37;
    R[4].address.address_plot=12;
    R[5].address.address_plot=76;
    R[6].address.address_plot=46;
    R[7].address.address_plot=4;
    //address x co-ordinates
    R[0].address.address_x=5225;
    R[1].address.address_x=5336;
    R[2].address.address_x=2543;
    R[3].address.address_x=3415;
    R[4].address.address_x=6521;
    R[5].address.address_x=1216;
    R[6].address.address_x=1632;
    R[7].address.address_x=845;
    //address y co-ordinates
    R[0].address.address_y=4325;
    R[1].address.address_y=2623;
    R[2].address.address_y=3232;
    R[3].address.address_y=5426;
    R[4].address.address_y=3219;
    R[5].address.address_y=4513;
    R[6].address.address_y=666;
    R[7].address.address_y=1634;
    //no. of general food items in each restaurant
    R[0].generalItemNum=10;
    R[1].generalItemNum=8;
    R[2].generalItemNum=9;
    R[3].generalItemNum=9;
    R[4].generalItemNum=7;
    R[5].generalItemNum=10;
    R[6].generalItemNum=6;
    R[7].generalItemNum=7;
    //general food items in each restaurant
    strcpy(R[0].general[0].name,"Hyderabadi Chicken Biryani\n");
    strcpy(R[0].general[1].name,"Chilli Chicken\n");
    strcpy(R[0].general[2].name,"Veg Biryani\n");
    strcpy(R[0].general[3].name,"Paneer Tikka Biryani\n"); 
    strcpy(R[0].general[4].name,"Veg Manchurian\n");
    strcpy(R[0].general[5].name,"Fish Fry\n");
    strcpy(R[0].general[6].name,"Veg Crispy\n"); 
    strcpy(R[0].general[7].name,"Veg Manchow Soup\n"); 
    strcpy(R[0].general[8].name,"Chicken Curry\n");
    strcpy(R[0].general[9].name,"Palak Paneer\n");
  
  
    strcpy(R[1].general[0].name,"Hyderabadi Chicken Biryani\n");
    strcpy(R[1].general[1].name,"Chicken Mughlai\n");
    strcpy(R[1].general[2].name,"Chicken Curry\n");
    strcpy(R[1].general[3].name,"Chicken Afghani\n");
    strcpy(R[1].general[4].name,"Veg Biryani\n");
    strcpy(R[1].general[5].name,"Paneer Biryani\n");
    strcpy(R[1].general[6].name,"Chicken Kolhapuri\n");
    strcpy(R[1].general[7].name,"Veg Kolhapuri\n");
     
    
    
    strcpy(R[2].general[0].name,"Crumbed Veg Jumbo Burger Meal\n");
    strcpy(R[2].general[1].name,"Crunchy Paneer Jumbo Burger Meal\n");
    strcpy(R[2].general[2].name,"Mexican Fried Chicken Burger Meal\n");
    strcpy(R[2].general[3].name,"In House Mutton Burger Meal\n");
    strcpy(R[2].general[4].name,"Deluxe Chicken Burger\n");
    strcpy(R[2].general[5].name,"Veggie Burger\n");
    strcpy(R[2].general[6].name,"Veg Fingers\n");
    strcpy(R[2].general[7].name,"Peri Peri French Fries\n");
    strcpy(R[2].general[8].name,"Crispy Fries\n");
   
   
   
    strcpy(R[3].general[0].name,"Chichen Popcorn\n");
    strcpy(R[3].general[1].name,"Peri Peri French Fries\n");
    strcpy(R[3].general[2].name,"Coleslaw Croissant\n");
    strcpy(R[3].general[3].name,"Pesto Paneer Sandwich\n");
    strcpy(R[3].general[4].name,"Mexican Veg Burger\n");
    strcpy(R[3].general[5].name,"Grilled Chicken Salad\n");
    strcpy(R[3].general[6].name,"Masala Cheese Omelette\n");
    strcpy(R[3].general[7].name,"Egg Benedict\n");
    strcpy(R[3].general[8].name,"Chichen Nuggets\n");
    
    
    
    strcpy(R[4].general[0].name,"Chichen biryani\n");
    strcpy(R[4].general[1].name,"Chichen Afghani\n");
    strcpy(R[4].general[2].name,"Chichen Kolhapuri\n");
    strcpy(R[4].general[3].name,"Paneer Kadai\n");
    strcpy(R[4].general[4].name,"Paneer Butter Masala\n");
    strcpy(R[4].general[5].name,"Egg Masala\n");
    strcpy(R[4].general[6].name,"Chilli Chicken\n");
    
    
    
    strcpy(R[5].general[0].name,"Veg Kolhapuri\n");
    strcpy(R[5].general[1].name,"Veg Handi\n");
    strcpy(R[5].general[2].name,"Paneer Punjabi\n");
    strcpy(R[5].general[3].name,"Veg Thali\n");
    strcpy(R[5].general[4].name,"Veg Hakka Noodles\n");
    strcpy(R[5].general[5].name,"Veg Schzewan Noodles\n");
    strcpy(R[5].general[6].name,"Veg Fried Rice\n");
    strcpy(R[5].general[7].name,"Veg Chilli Garlic Noodles\n");
    strcpy(R[5].general[8].name,"Masala Paneer Thali\n");
    strcpy(R[5].general[9].name,"Veg Crispy\n");
    
    
    
    strcpy(R[6].general[0].name,"Belgian Chocolate Cake\n");
    strcpy(R[6].general[1].name,"Belgian Chocolate CheeseCake\n");
    strcpy(R[6].general[2].name,"Nutella Filled Berliner Doughnut\n");
    strcpy(R[6].general[3].name,"Mixed Fruit And Berries Cake\n");
    strcpy(R[6].general[4].name,"Chocolate Truffle Cake\n");
    strcpy(R[6].general[5].name,"Dutch Truffle Cake\n");
    
    
    
    strcpy(R[7].general[0].name,"Veg Hakka Noodles\n");
    strcpy(R[7].general[1].name,"Veg Schzewan Noodles\n");
    strcpy(R[7].general[2].name,"Veg Crispy\n");
    strcpy(R[7].general[3].name,"Chilli Chicken\n");
    strcpy(R[7].general[4].name,"Chicken Lollipop\n");
    strcpy(R[7].general[5].name,"Veg Manchow Soup\n");
    strcpy(R[7].general[6].name,"Egg Fried Rice\n");
    
    
    //costs of general items
    R[0].general[0].price=330;
    R[0].general[1].price=499;
    R[0].general[2].price=290;
    R[0].general[3].price=320;
    R[0].general[4].price=260;
    R[0].general[5].price=320;
    R[0].general[6].price=260;
    R[0].general[7].price=290;
    R[0].general[8].price=280;
    R[0].general[9].price=290;
    
    
    R[1].general[0].price=220;
    R[1].general[1].price=149;
    R[1].general[2].price=139;
    R[1].general[3].price=149;
    R[1].general[4].price=210;
    R[1].general[5].price=220;
    R[1].general[6].price=139;
    R[1].general[7].price=129;
    
    
    R[2].general[0].price=377;
    R[2].general[1].price=477;
    R[2].general[2].price=399;
    R[2].general[3].price=469;
    R[2].general[4].price=179;
    R[2].general[5].price=165;
    R[2].general[6].price=198;
    R[2].general[7].price=129;
    R[2].general[8].price=119;
    
    
    R[3].general[0].price=260;
    R[3].general[1].price=240;
    R[3].general[2].price=245;
    R[3].general[3].price=285;
    R[3].general[4].price=260;
    R[3].general[5].price=340;
    R[3].general[6].price=260;
    R[3].general[7].price=310;
    R[3].general[8].price=235;
    
    
    R[4].general[0].price=230;
    R[4].general[1].price=150;
    R[4].general[2].price=150;
    R[4].general[3].price=140;
    R[4].general[4].price=140;
    R[4].general[5].price=130;
    R[4].general[6].price=140;
    R[4].general[7].price=190;
    
    
    
    R[5].general[0].price=230;
    R[5].general[1].price=220;
    R[5].general[2].price=220;
    R[5].general[3].price=360;
    R[5].general[4].price=180;
    R[5].general[5].price=210;
    R[5].general[6].price=220;
    R[5].general[7].price=230;
    R[5].general[8].price=140;
    R[5].general[9].price=130;
    
    
    
    R[6].general[0].price=750;
    R[6].general[1].price=89;
    R[6].general[2].price=150;
    R[6].general[3].price=675;
    R[6].general[4].price=670;
    R[6].general[5].price=575;
    
    
    
    R[7].general[0].price=150;
    R[7].general[1].price=160;
    R[7].general[2].price=130;
    R[7].general[3].price=190;
    R[7].general[4].price=185;
    R[7].general[5].price=185;
    R[7].general[6].price=160;
    
    
    //serve time of general items
    R[0].general[0].serv_tym=35;
    R[0].general[1].serv_tym=40;
    R[0].general[2].serv_tym=40;
    R[0].general[3].serv_tym=30;
    R[0].general[4].serv_tym=35;
    R[0].general[5].serv_tym=30;
    R[0].general[6].serv_tym=40;
    R[0].general[7].serv_tym=25;
    R[0].general[8].serv_tym=25;
    R[0].general[9].serv_tym=26;
    
    
    R[1].general[0].serv_tym=30;
    R[1].general[1].serv_tym=32;
    R[1].general[2].serv_tym=35;
    R[1].general[3].serv_tym=35;
    R[1].general[4].serv_tym=30;
    R[1].general[5].serv_tym=25;
    R[1].general[6].serv_tym=25;
    R[1].general[7].serv_tym=25;
    
    
    R[2].general[0].serv_tym=30;
    R[2].general[1].serv_tym=35;
    R[2].general[2].serv_tym=40;
    R[2].general[3].serv_tym=40;
    R[2].general[4].serv_tym=40;
    R[2].general[5].serv_tym=35;
    R[2].general[6].serv_tym=35;
    R[2].general[7].serv_tym=30;
    R[2].general[8].serv_tym=30;
    
    
    R[3].general[0].serv_tym=30;
    R[3].general[1].serv_tym=30;
    R[3].general[2].serv_tym=35;
    R[3].general[3].serv_tym=36;
    R[3].general[4].serv_tym=26;
    R[3].general[5].serv_tym=34;
    R[3].general[6].serv_tym=35;
    R[3].general[7].serv_tym=35;
    R[3].general[8].serv_tym=30;
    
    
    R[4].general[0].serv_tym=40;
    R[4].general[1].serv_tym=40;
    R[4].general[2].serv_tym=42;
    R[4].general[3].serv_tym=40;
    R[4].general[4].serv_tym=40;
    R[4].general[5].serv_tym=45;
    R[4].general[6].serv_tym=46;
    R[4].general[7].serv_tym=44;
    
    
    
    R[5].general[0].serv_tym=30;
    R[5].general[1].serv_tym=35;
    R[5].general[2].serv_tym=35;
    R[5].general[3].serv_tym=35;
    R[5].general[4].serv_tym=30;
    R[5].general[5].serv_tym=30;
    R[5].general[6].serv_tym=30;
    R[5].general[7].serv_tym=35;
    R[5].general[8].serv_tym=36;
    R[5].general[9].serv_tym=36;
    
    
    
    R[6].general[0].serv_tym=60;
    R[6].general[1].serv_tym=50;
    R[6].general[2].serv_tym=55;
    R[6].general[3].serv_tym=65;
    R[6].general[4].serv_tym=65;
    R[6].general[5].serv_tym=65;
    
    
    
    R[7].general[0].serv_tym=30;
    R[7].general[1].serv_tym=25;
    R[7].general[2].serv_tym=25;
    R[7].general[3].serv_tym=30;
    R[7].general[4].serv_tym=25;
    R[7].general[5].serv_tym=30;
    R[7].general[6].serv_tym=30;
    
    
    //spl item num in each restaurant
    
    R[0].splItemNum=3;
    R[1].splItemNum=4;
    R[2].splItemNum=2;
    R[3].splItemNum=3;
    R[4].splItemNum=4;
    R[5].splItemNum=3;
    R[6].splItemNum=2;
    R[7].splItemNum=3;
    
    // spl items in each restaurants
    
    strcpy(R[0].spl_item[0].name,"Malabar Chicken Biryani\n");
    strcpy(R[0].spl_item[1].name,"Chicken Afghani\n");
    strcpy(R[0].spl_item[2].name,"Chicken Kolhapuri\n");
    
    strcpy(R[1].spl_item[0].name,"Mughlai Chicken Biryani\n");
    strcpy(R[1].spl_item[1].name,"Tandoori Chicken\n");
    strcpy(R[1].spl_item[2].name,"Chicken Manchurian\n");
    strcpy(R[1].spl_item[3].name,"Lucknow Chicken Biryani\n");
    
    strcpy(R[2].spl_item[0].name,"Chef's Special Chicken Jumbo Burger\n");
    strcpy(R[2].spl_item[1].name,"Choco Lava Cake\n");
    
    strcpy(R[3].spl_item[0].name,"Margarita Pizza\n");
    strcpy(R[3].spl_item[1].name,"Seven O' Eleven Special Pizza\n");
    strcpy(R[3].spl_item[2].name,"Virgin Mojito\n");
    
    strcpy(R[4].spl_item[0].name,"Bhangra Masala\n");
    strcpy(R[4].spl_item[1].name,"Fish Fry\n");
    strcpy(R[4].spl_item[2].name,"BBQ Chicken\n");
    strcpy(R[4].spl_item[3].name,"Lamb Curry\n");
    
    strcpy(R[5].spl_item[0].name,"Paneer Masala\n");
    strcpy(R[5].spl_item[1].name,"Palak Paneer\n");
    strcpy(R[5].spl_item[2].name,"Veg Kofta\n");
    
    strcpy(R[6].spl_item[0].name,"Belgian Chocolate And Strawberry cake\n");
    strcpy(R[6].spl_item[1].name,"Black Forest 2.O\n");
    
    strcpy(R[7].spl_item[0].name,"Hong Kong Noodles\n");
    strcpy(R[7].spl_item[1].name,"Chicken Spicy Fried Rice\n");
    strcpy(R[7].spl_item[2].name,"Chicken Dry Manchurian\n");
    
    //spl items prices
    
    R[0].spl_item[0].price=250;
    R[0].spl_item[1].price=169;
    R[0].spl_item[2].price=169;
    
    R[1].spl_item[0].price=320;
    R[1].spl_item[1].price=450;
    R[1].spl_item[2].price=300;
    R[1].spl_item[3].price=320;
    
    R[2].spl_item[0].price=259;
    R[2].spl_item[1].price=89;
    
    R[3].spl_item[0].price=260;
    R[3].spl_item[1].price=365;
    R[3].spl_item[2].price=130;
    
    R[4].spl_item[0].price=140;
    R[4].spl_item[1].price=150;
    R[4].spl_item[2].price=430;
    R[4].spl_item[3].price=440;
    
    R[5].spl_item[0].price=120;
    R[5].spl_item[1].price=130;
    R[5].spl_item[2].price=139;
    
    R[6].spl_item[0].price=1300;
    R[6].spl_item[1].price=1100;
    
    R[7].spl_item[0].price=120;
    R[7].spl_item[1].price=130;
    R[7].spl_item[2].price=130;
    
    //serve times of spl items
    R[0].spl_item[0].serv_tym=25;
    R[0].spl_item[1].serv_tym=30;
    R[0].spl_item[2].serv_tym=30;
    
    R[1].spl_item[0].serv_tym=35;
    R[1].spl_item[1].serv_tym=35;
    R[1].spl_item[2].serv_tym=30;
    R[1].spl_item[3].serv_tym=32;
    
    R[2].spl_item[0].serv_tym=25;
    R[2].spl_item[1].serv_tym=30;
    
    R[3].spl_item[0].serv_tym=25;
    R[3].spl_item[1].serv_tym=30;
    R[3].spl_item[2].serv_tym=35;
    
    R[4].spl_item[0].serv_tym=40;
    R[4].spl_item[1].serv_tym=45;
    R[4].spl_item[2].serv_tym=43;
    R[4].spl_item[3].serv_tym=45;
    
    R[5].spl_item[0].serv_tym=30;
    R[5].spl_item[1].serv_tym=30;
    R[5].spl_item[2].serv_tym=35;
    
    R[6].spl_item[0].serv_tym=50;
    R[6].spl_item[1].serv_tym=60;
    
    R[7].spl_item[0].serv_tym=30;
    R[7].spl_item[1].serv_tym=30;
    R[7].spl_item[2].serv_tym=30;
    
    //item of the Day
    
    strcpy(R[0].itemOfTheDay.name,"Tandoori Chicken\n");
    strcpy(R[1].itemOfTheDay.name,"Malai Chicken Biryani\n");
    strcpy(R[2].itemOfTheDay.name,"Chicken Popcorn\n");
    strcpy(R[3].itemOfTheDay.name,"Chicken Lasagne\n");
    strcpy(R[4].itemOfTheDay.name,"Chicken Handi\n");
    strcpy(R[5].itemOfTheDay.name,"Royal Paneer Thali\n");
    strcpy(R[6].itemOfTheDay.name,"Blueberry Cheesecake\n");
    strcpy(R[7].itemOfTheDay.name,"Chicken Cheese Momos\n");
    
    // item of the day prices
    
     R[0].itemOfTheDay.price=450;
     R[1].itemOfTheDay.price=320;
     R[2].itemOfTheDay.price=360;
     R[3].itemOfTheDay.price=520;
     R[4].itemOfTheDay.price=220;
     R[5].itemOfTheDay.price=330;
     R[6].itemOfTheDay.price=175;    
     R[7].itemOfTheDay.price=120;
    
    //item of the day serve time
    
    R[0].itemOfTheDay.serv_tym=40;
    R[1].itemOfTheDay.serv_tym=30;
    R[2].itemOfTheDay.serv_tym=30;
    R[3].itemOfTheDay.serv_tym=45;
    R[4].itemOfTheDay.serv_tym=30;
    R[5].itemOfTheDay.serv_tym=25;
    R[6].itemOfTheDay.serv_tym=35;
    R[7].itemOfTheDay.serv_tym=35;   
               
    printf("Welcome!!!\n");  
    int res=8;
    int i;
    int press,out;
    int input_res;
    char input_R[res][50];
    food_order myList[10];
    char item[50];
    int quantity;
    full_address user_address;
    char item_2[50];
    int items_no;
    int ordernum=2;
    char res_name[50];
    char area_need2[50];
    char area_need3[50];    
    printf("The restaurants available with us are\n");
    qsort_res(R,0,res-1);
    for(i=0;i<res;i++) {
    printf("%s\n",R[i].name);
    }
    printf("PRESS\n");
    printf("1\tMinimum Time\n2\tAvailability of an item\n3\tPlace an Order\n4\tSorted Item List\n5\tItems near you\n6\tspecial items\n7\tItems of the day\n8\tCommon items\n9\tunique items\n10\texit\n");
    scanf("%d",&press);
    switch(press) {
     case 1:
       printf("Enter the item you would like to have\n");
       getchar();
       fgets(item,50,stdin);
       printf("Enter the quantity");
       scanf("%d",&quantity);
       printf("Also enter your plot's x and y co-ordinates\n");
       scanf("%d %d",&user_address.address_x,&user_address.address_y);
       getMinTime(item,quantity,R,user_address,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       }
     case 2:
       printf("Enter The item you are craving for\n");
       getchar();
       fgets(item_2,50,stdin);
       getItemAvailability(item_2,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 3:
       printf("Enter No. of different items you wish to have\n");
       scanf("%d",&items_no);
       printf("First enter the items and then their respective quantites: \n");
       getchar();
       for(i=0;i<items_no;i++) {
           fgets(myList[i].name,50,stdin);
           
       }
       for(i=0;i<items_no;i++) {
        scanf("%d",&myList[i].quantity);
       }
       printf("Enter your address co-ordinates:\n");
       scanf("%d %d",&user_address.address_x,&user_address.address_y);
       placeAnOrder(myList,items_no,user_address,ordernum,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 4:

       printf("Enter the restaurant name\n");
       getchar();
       fgets(res_name,50,stdin);
       getItemListInSortedOrder(res_name,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 5:
      printf("Enter your Area:\n");
      getchar();
       fgets(area_need2,50,stdin);
       getItemListInAreaSortedOrder(area_need2,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 6:
       printf("Enter no. of restaurants");
       scanf("%d",&input_res);
       printf("Enter the restaurants list:\n");
       getchar();
       for(i=0;i<input_res;i++) {
       fgets(input_R[i],50,stdin);
       }
       getAllSpecialItemListInOrder(R,res,input_R,input_res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 7:
       printf("Enter Your Area:\n");
       getchar();
       fgets(area_need3,50,stdin);
       getItemOfDayListInSortedOrder(area_need3,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 8:
       printf("Enter no. of restaurants");
       scanf("%d",&input_res);
       printf("Enter the restaurants list:\n");
       getchar();
       for(i=0;i<input_res;i++) {
       fgets(input_R[i],50,stdin);
       }
       getCommonItem(input_R,input_res,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 9:
       printf("Enter no. of restaurants");
       scanf("%d",&input_res);
       printf("Enter the restaurants list:\n");
       getchar();
       for(i=0;i<input_res;i++) {
       fgets(input_R[i],50,stdin);
       }
       getUniqueItem(input_R,input_res,R,res);
       printf("Do you want to continue with us??\n");
       printf("Press\n 1\tYes\t\t0\tNo\n");
       scanf("%d",&out);
       if(out==0) {
          press=10;
          break;
       }
       else {
          printf("Enter which operation you want to do\n");
          scanf("%d",&press);
       } 
     case 10:
        printf("Thank you!!! Visit Again");
        break;  
      }
    }


