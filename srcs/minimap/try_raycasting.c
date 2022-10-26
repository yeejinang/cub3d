// #include <mlx.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <stdbool.h>

// #define mapWidth 24
// #define mapHeight 24
// #define screenWidth 640
// #define screenHeight 480

// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// int main(int argc, char *argv[])
// {
//   double posX = 22, posY = 12;
//   double dirX = -1, dirY = 0; 
//   double planeX = 0, planeY = 0.64;

//   int w = 10;

// //   while(true)
// //   {
// 	for(int x = 0; x < w; x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;
// 	//   printf("rayDir X: %f\t Y: %f\n", rayDirX, rayDirY);

// 	  //which box of the map we're in
//       int mapX = (int)posX;
//       int mapY = (int)posY;

//       //length of ray from current position to next x or y-side
//       double sideDistX; //till it hits horizontal line
//       double sideDistY; //till it hits vertical line

//        //length of ray from one x or y-side to next x or y-side
// 	   //deltaDist X and deltaDist Y is not the actual distance, but ratio X : Y
//       double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//       double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
// 	//   printf("delta Dist X: %f\t Y: %f\n", deltaDistX, deltaDistY);
//       double perpWallDist;

//       //what direction to step in x or y-direction (either +1 or -1)
//       int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?

// 		//to see check the map on this direction
// 	   if (rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//       }
//       if (rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//       }
// 	//   printf("side Dist X: %f\t Y: %f\n", sideDistX, sideDistY);

// 	  while (hit == 0)
//       {
//         //jump to next map square, either in x-direction, or in y-direction
//         if (sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if (worldMap[mapX][mapY] > 0)
// 		{
// 			hit = 1;
// 			//try draw line
// 			// x1: y1: 
// 			printf("sideDist X: %f\t Y: %f\n", sideDistX, sideDistY);
// 			printf("delta X: %f\t Y: %f\n", deltaDistX, deltaDistY);
// 			printf("mapX: %d\t mapY: %d\n", mapX, mapY);
// 		}
//       }
// 	}
// //   } 
// }