
<div><p><br/>
</p>
<h2><span id="MODT">MODT</span></h2>
<h3><span id="Version_&gt;=40"></span><span id="Version_.3E.3D40">Version &gt;=40</span></h3>
<p>If form version is &gt;=40.
</p>
<h4><span id="Header">Header</span></h4>
<table class="wikitable">
<tbody><tr>
<th>Name
</th>
<th><a href="File_Format_Conventions.html">Type/Size</a>
</th>
<th>Info
</th></tr>
<tr>
<td>count</td>
<td>uint32</td>
<td><i>type? 02-00-00-00-00-00-00-00-00-00-00-00 is a blank collidable record</i>
</td></tr>
<tr>
<td>unknown4count</td>
<td>uint32</td>
<td>Only present if count &gt;= 1, otherwise default 0.
</td></tr>
<tr>
<td>unknown5count</td>
<td>uint32</td>
<td>Only present if count &gt;= 2, otherwise default 0.
</td></tr>
<tr>
<td>unknown3</td>
<td>uint32[count-2]</td>
<td>Only present if count &gt;= 3.
</td></tr>
<tr>
<td>unknown4</td>
<td><a href="#Unknown4">Unknown4</a>[unknown4count]</td>
<td>
</td></tr>
<tr>
<td>unknown5</td>
<td>uint32[unknown5count]</td>
<td>
</td></tr></tbody></table>
<h4><span id="Unknown4">Unknown4</span></h4>
<table class="wikitable">
<tbody><tr>
<th>Name
</th>
<th><a href="File_Format_Conventions.html">Type/Size</a>
</th>
<th>Info
</th></tr>
<tr>
<td>unknown</td>
<td>uint32</td>
<td>
</td></tr>
<tr>
<td>texture type?</td>
<td>char[4]</td>
<td>dds\0
</td></tr>
<tr>
<td>unknown</td>
<td>uint32</td>
<td><i>common format data? commonly repeats with one or two outliers'</i>
</td></tr></tbody></table>
<h3><span id="Version_&gt;=38"></span><span id="Version_.3E.3D38">Version &gt;=38</span></h3>
<p>If form version is &gt;=38 &amp;&amp; &lt;40.
</p>
<h4><span id="Header_2">Header</span></h4>
<table class="wikitable">
<tbody><tr>
<th>Name
</th>
<th><a href="File_Format_Conventions.html">Type/Size</a>
</th>
<th>Info
</th></tr>
<tr>
<td>unknown</td>
<td><a href="#Unknown0">Unknown0</a>[field data size / 12]</td>
<td>
</td></tr></tbody></table>
<h4><span id="Unknown0">Unknown0</span></h4>
<table class="wikitable">
<tbody><tr>
<th>Name
</th>
<th><a href="File_Format_Conventions.html">Type/Size</a>
</th>
<th>Info
</th></tr>
<tr>
<td>unknown</td>
<td>uint32</td>
<td>
</td></tr>
<tr>
<td>unknown</td>
<td>char[4]</td>
<td>dds\0
</td></tr>
<tr>
<td>unknown</td>
<td>uint32</td>
<td>
</td></tr></tbody></table>
</div>