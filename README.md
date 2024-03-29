fleet                                                               {#mainpage}
=====

A game of space warfare!

Right now the game is mostly just me playing with the Ogre engine, but I'm
hoping to develop it into something that I can actually play.

The basic premise is that you start off with a tiny little ship, but through
{combat, trade, diplomacy} you acquire bigger and bigger ships, and gain
AI-controlled allies (or are they?). Perhaps the local Trade Alliance / Galactic
Federation notices you, and tries to {blow you up, hire you, establish a trade
embargo against you}.

Of course, none of this is implemented quite yet :)

License
-------

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.

Installing
----------

The build system uses CMake, which should be available on your platform.

You'll need to:

1. Install OGRE (either from your platform's repository, or by building from
   source).

2. Install OIS.

3. Install Bullet (the physics engine).

4. Install OgreBullet (the OGRE wrapper for Bullet).

5. Build fleet.

Ideally, building fleet is as simple as:

cmake . -G "Unix Makefiles"

make

But I've only ever built it on my machine. If you have trouble building fleet,
please send me an email! (Or even if you build it at all)

Running
-------

After building fleet, you'll need some config files to tell OGRE where the game
resources are. Eventually, I'll get around to fixing this system up.

Specifically, you'll need _plugins.cfg_ and _resources.cfg_. The OGRE forums
can definitely provide you with more information than I can.

