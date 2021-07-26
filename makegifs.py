import imageio
import os

fs = []
for files, dirs, x in os.walk('frames/'):
    fs = x

#with imageio.get_writer('anim.gif', mode='I') as writer:
images = []
for f in sorted(fs):
    image = imageio.imread('frames/' + f)
    images.append(image)

imageio.mimsave("anim.gif", images, 'GIF', fps=18)
#        writer.append_data(image)

