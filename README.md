## RG109-shorka

### Short description
This is a Computer Graphics course project - First person shooter game vs bots.<br /><br />
Each players' bullet takes 30hp from bot, so every bot should be hit 4 times. Bots are changing colors depending on their health percentage.<br />
Bots are little bit weaker than player, so their bullet takes 15hp from player.

### Build:
Navigate to root folder of project (RG109-shorka) and then just <br />
`make` 

### Usage:
`./shorka num_of_bots` 
where num_of_bots represent number between 0 and 8 which will be number of bots playing versus player. <br />
If num_of_bots isn't specified, default number of bots will be 1.

### Controls:
| Key | Description|
| :-------------: | :-----------------: |
| `W` | move forward |
| `A` | move left |
| `S` | move backward |
| `D` | move right |
| `P` | pause game |
| `space` | jump |
| `mouse motion` | moving camera view |
| `left click` | shoot |
